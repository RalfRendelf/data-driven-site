#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

class TimerManager {
public:
    TimerManager() : running(false), nextId(1) {}

    ~TimerManager() {
        stop();
    }

    int addTimer(std::chrono::milliseconds interval,
                 std::function<void()> callback)
    {
        std::lock_guard<std::mutex> lock(mutex);

        int id = nextId++;
        timers.push_back(Timer{
            id,
            interval,
            std::chrono::steady_clock::now() + interval,
            std::move(callback)
        });

        cv.notify_one();
        return id;
    }

    void removeTimer(int id)
    {
        std::lock_guard<std::mutex> lock(mutex);
        timers.erase(
            std::remove_if(timers.begin(), timers.end(),
                           [id](const Timer& t){ return t.id == id; }),
            timers.end()
        );
        cv.notify_one();
    }

    void start()
    {
        bool expected = false;
        if (!running.compare_exchange_strong(expected, true))
            return; // уже запущен

        worker = std::thread([this] { run(); });
    }

    void stop()
    {
        bool expected = true;
        if (!running.compare_exchange_strong(expected, false))
            return; // уже остановлен

        cv.notify_one();
        if (worker.joinable())
            worker.join();
    }

private:
    struct Timer {
        int id;
        std::chrono::milliseconds interval;
        std::chrono::steady_clock::time_point nextRun;
        std::function<void()> callback;
    };

    std::vector<Timer> timers;
    std::mutex mutex;
    std::condition_variable cv;
    std::atomic<bool> running;
    std::thread worker;
    int nextId;

    void run()
    {
        std::unique_lock<std::mutex> lock(mutex);

        while (running) {
            if (timers.empty()) {
                cv.wait(lock, [this] { return !running || !timers.empty(); });
                continue;
            }

            auto now = std::chrono::steady_clock::now();

            // Найти ближайший таймер
            auto nextTimerIt = std::min_element(
                timers.begin(), timers.end(),
                [](const Timer& a, const Timer& b) {
                    return a.nextRun < b.nextRun;
                }
            );

            if (cv.wait_until(lock, nextTimerIt->nextRun,
                              [this]{ return !running; }))
            {
                continue; // stop() вызван
            }

            now = std::chrono::steady_clock::now();
            if (now >= nextTimerIt->nextRun) {
                auto callback = nextTimerIt->callback;
                nextTimerIt->nextRun += nextTimerIt->interval;

                lock.unlock();
                callback();     // выполняем без блокировки
                lock.lock();
            }
        }
    }
};
 