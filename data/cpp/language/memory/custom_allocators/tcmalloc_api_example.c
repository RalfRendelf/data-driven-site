#include <stdio.h>
#include <gperftools/tcmalloc.h>

// Рекомендация: Используйте для приложений, где требуется явный контроль над выделением памяти.
int main() {
    // Выделение памяти с помощью tcmalloc
    int* ptr = (int*)tc_malloc(sizeof(int) * 10);
    if (ptr == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    ptr[0] = 42;
    printf("%d\n", ptr[0]);

    // Освобождение памяти
    tc_free(ptr);

    return 0;
}
