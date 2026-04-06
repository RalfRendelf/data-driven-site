import { CATEGORIES } from "./categories.js";
import { generateTreeStructure } from "./generator.js";

document.addEventListener("DOMContentLoaded", async () => {
  // Заполняем боковую панель категориями
  const navElement = document.getElementById("categories-nav");
  if (navElement) {
    const navHTML = `
      <ul>
        ${CATEGORIES.map((cat, index) => `
          <li>
            <a href="#" data-category="${cat.type}" data-index="${index}">
              ${cat.title}
            </a>
          </li>
        `).join("")}
      </ul>
    `;
    navElement.innerHTML = navHTML;
    
    // Добавляем обработчик кликов по категориям
    document.querySelectorAll('#categories-nav a').forEach(link => {
      link.addEventListener('click', function(e) {
        e.preventDefault();
        
        // Проверяем, есть ли у текущей ссылки класс active
        const isActive = this.classList.contains('active');
        
        // Убираем активный класс со всех ссылок
        document.querySelectorAll('#categories-nav a').forEach(a => {
          a.classList.remove('active');
        });
        
        // Если текущая ссылка не была активной, добавляем ей класс active
        if (!isActive) {
          this.classList.add('active');
          
          // Получаем тип категории
          const categoryType = this.getAttribute('data-category');
          
          // Отображаем дерево для выбранной категории
          displayTreeForCategory(categoryType);
        }
      });
    });
  }
  
  // Генерируем древовидную структуру
  await generateTreeStructure();
  
  // Добавляем функциональность для кнопок сворачивания
  setupToggleButtons();
  
  // Добавляем функциональность поиска
  setupGlobalSearch();
});

// Функция для отображения дерева для выбранной категории
function displayTreeForCategory(categoryType) {
  // Находим соответствующую категорию в CATEGORIES
  const category = CATEGORIES.find(cat => cat.type === categoryType);
  
  if (!category) {
    console.error(`Категория с типом ${categoryType} не найдена`);
    return;
  }
  
  // Получаем контейнер для отображения содержимого
  const contentArea = document.querySelector('.content-area');
  
  // Очищаем содержимое
  contentArea.innerHTML = '';
  
  // Создаем заголовок
  const header = document.createElement('h2');
  header.textContent = category.title;
  contentArea.appendChild(header);
  
  // Загружаем и отображаем данные для категории
  loadAndDisplayCategoryData(category);
}

// Функция для загрузки и отображения данных категории
async function loadAndDisplayCategoryData(category) {
  try {
    // Загружаем index.json для категории
    const response = await fetch(`data/${category.type}/index.json`);
    if (!response.ok) {
      throw new Error(`Не удалось загрузить data/${category.type}/index.json`);
    }
    
    const jsonData = await response.json();
    
    // Создаем таблицу
    const table = document.createElement('table');
    table.className = 'category-table';
    
    // Создаем заголовок таблицы
    const thead = document.createElement('thead');
    const headerRow = document.createElement('tr');
    
    // Добавляем колонки из category.columns
    category.columns.forEach(col => {
      const th = document.createElement('th');
      th.textContent = col;
      headerRow.appendChild(th);
    });
    
    thead.appendChild(headerRow);
    table.appendChild(thead);
    
    // Создаем тело таблицы
    const tbody = document.createElement('tbody');
    
    // Заполняем строки данными из jsonData
    jsonData.forEach(item => {
      const row = document.createElement('tr');
      row.className = 'entry';
      row.dataset.file = item.fileName;
      row.dataset.isLeaf = item.isLeaf || false;
      
      // Заполняем колонки: name, category, usage
      const nameCell = document.createElement('td');
      nameCell.textContent = item.name;
      row.appendChild(nameCell);
      
      const categoryCell = document.createElement('td');
      categoryCell.textContent = item.category;
      row.appendChild(categoryCell);
      
      const usageCell = document.createElement('td');
      usageCell.textContent = item.usage;
      row.appendChild(usageCell);
      
      tbody.appendChild(row);
    });
    
    table.appendChild(tbody);
    document.querySelector('.content-area').appendChild(table);
  } catch (error) {
    console.error(`Ошибка при загрузке данных для категории ${category.type}:`, error);
    
    // Показываем сообщение об ошибке
    const errorMessage = document.createElement('p');
    errorMessage.textContent = `Ошибка загрузки данных для ${category.title}`;
    errorMessage.style.color = 'red';
    document.querySelector('.content-area').appendChild(errorMessage);
  }
}

// Функция для настройки кнопок сворачивания/разворачивания
  function setupToggleButtons() {
    // Кнопка для сворачивания/разворачивания боковой панели
    // const toggleSidebarBtn = document.getElementById('toggle-sidebar');
    // if (toggleSidebarBtn) {
    //   toggleSidebarBtn.addEventListener('click', () => {
    //     const sidebar = document.querySelector('.sidebar');
    //     const container = document.querySelector('.main-container');
        
    //     sidebar.classList.toggle('hidden');
    //     container.classList.toggle('sidebar-hidden');
        
    //     // Поворачиваем кнопку для визуального эффекта
    //     toggleSidebarBtn.classList.toggle('rotated');
        
    //     // Изменяем символ на кнопке
    //     toggleSidebarBtn.textContent = sidebar.classList.contains('hidden') ? 'Скрыть' : 'Показать';
    //   });
    // }
  
  // Кнопка для скрытия/отображения тем
  const toggleThemesBtn = document.getElementById('toggle-themes');
  if (toggleThemesBtn) {
    toggleThemesBtn.addEventListener('click', () => {
      const sidebar = document.querySelector('.sidebar');
      const container = document.querySelector('.main-container');
      
      sidebar.classList.toggle('hidden');
      container.classList.toggle('themes-hidden');
      
      // Поворачиваем кнопку для визуального эффекта
      toggleThemesBtn.classList.toggle('rotated');
      
      // Изменяем символ на кнопке
      toggleThemesBtn.textContent = sidebar.classList.contains('hidden') ? 'Открыть' : 'Скрыть';
    });
  }
}

// Функция для настройки глобального поиска по всему дереву
function setupGlobalSearch() {
  const searchBox = document.getElementById('search-box');
  if (searchBox) {
    searchBox.addEventListener('input', async (e) => {
      const searchTerm = e.target.value.toLowerCase();
      
      if (!searchTerm) {
        // Если поле поиска пустое, восстанавливаем обычное состояние
        document.querySelectorAll('.entry').forEach(row => {
          row.style.display = '';
          if (row.nextElementSibling && row.nextElementSibling.classList.contains('detail')) {
            row.nextElementSibling.style.display = 'none';
          }
        });
        return;
      }
      
      // Скрываем все строки таблиц
      document.querySelectorAll('.entry').forEach(row => {
        row.style.display = 'none';
        if (row.nextElementSibling && row.nextElementSibling.classList.contains('detail')) {
          row.nextElementSibling.style.display = 'none';
        }
      });
      
      // Показываем только подходящие результаты
      document.querySelectorAll('.entry').forEach(row => {
        const nameText = row.cells[0].textContent.toLowerCase(); // name
        const categoryText = row.cells[1].textContent.toLowerCase(); // category
        const usageText = row.cells[2].textContent.toLowerCase(); // usage
        
        if (nameText.includes(searchTerm) || 
            categoryText.includes(searchTerm) || 
            usageText.includes(searchTerm)) {
          row.style.display = '';
        }
      });
    });
  }
}