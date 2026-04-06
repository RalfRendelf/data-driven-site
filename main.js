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