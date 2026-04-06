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
  const treeContainer = await generateTreeStructure();
  
  // Добавляем атрибут data-type к таблицам для отслеживания типа категории
  if (treeContainer) {
    CATEGORIES.forEach(category => {
      const table = treeContainer.querySelector(`.category-table`);
      if (table) {
        table.dataset.type = category.type;
      }
    });
  }
  
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
  loadAndDisplayCategoryDataRecursively(category).then(table => {
    if (table) {
      contentArea.appendChild(table);
    }
  });
}

// Рекурсивная функция для загрузки и отображения данных категории
async function loadAndDisplayCategoryDataRecursively(category, basePath = null) {
  try {
    // Формируем путь к файлу
    const path = basePath ? `data/${basePath}/index.json` : `data/${category.type}/index.json`;
    
    // Загружаем index.json для категории
    const response = await fetch(path);
    if (!response.ok) {
      throw new Error(`Не удалось загрузить ${path}`);
    }
    
    const jsonData = await response.json();
    
    // Создаем таблицу
    const table = document.createElement('table');
    table.className = basePath ? 'category-table nested' : 'category-table';
    
    // Добавляем атрибут data-type для отслеживания типа категории
    if (!basePath) {
      table.dataset.type = category.type;
    }
    
    if (!basePath) {
      table.style.marginLeft = '0';
    } else {
      table.style.marginLeft = '20px';
    }
    
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
    for (const item of jsonData) {
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
      
      // Добавляем обработчик клика для открытия/закрытия скрытых частей
      row.addEventListener('click', async function(e) {
        e.stopPropagation();
        
        const isLeaf = this.dataset.isLeaf === 'true';
        const fileName = this.dataset.file;
        const currentBasePath = basePath ? `${basePath}/${fileName}` : `${category.type}/${fileName}`;
        
        // Находим следующий элемент (детализация)
        let detailRow = this.nextElementSibling;
        
        // Проверяем, существует ли уже строка детализации и является ли она detail
        if (detailRow && detailRow.classList.contains('detail')) {
          // Если строка уже открыта, закрываем её
          if (detailRow.style.display === 'table-row') {
            detailRow.style.display = 'none';
            return;
          } else {
            // Если строка закрыта, открываем её
            detailRow.style.display = 'table-row';
            return;
          }
        } else {
          // Создаем строку детализации
          detailRow = document.createElement('tr');
          detailRow.className = 'detail';
          detailRow.style.display = 'none';
          detailRow.innerHTML = '<td colspan="3"><div class="content">Загрузка...</div></td>';
          
          // Вставляем после текущей строки
          this.parentNode.insertBefore(detailRow, this.nextSibling);
        }
        
        // Если элемент - лист, загружаем содержимое статьи
        if (isLeaf) {
          try {
            const articleContent = await fetch(`data/${currentBasePath}/index.txt`).then(r => r.text());
            detailRow.querySelector('.content').innerHTML = articleContent;
            detailRow.style.display = 'table-row';
          } catch (err) {
            console.error('Ошибка загрузки статьи:', err);
            detailRow.querySelector('.content').textContent = '❌ Ошибка загрузки статьи.';
          }
        } else {
          // Если элемент не лист, рекурсивно загружаем подкатегорию
          try {
            // Рекурсивно вызываем функцию для загрузки вложенной структуры
            const nestedContent = await loadAndDisplayCategoryDataRecursivelyInternal(
              category, 
              currentBasePath
            );
            
            detailRow.querySelector('.content').innerHTML = '';
            detailRow.querySelector('.content').appendChild(nestedContent);
            detailRow.style.display = 'table-row';
          } catch (err) {
            console.error('Ошибка загрузки подкатегории:', err);
            detailRow.querySelector('.content').textContent = '❌ Ошибка загрузки подкатегории.';
          }
        }
      });
      
      tbody.appendChild(row);
    }
    
    table.appendChild(tbody);
    return table;
  } catch (error) {
    console.error(`Ошибка при загрузке данных:`, error);
    
    // Показываем сообщение об ошибке
    const errorMessage = document.createElement('p');
    errorMessage.textContent = `Ошибка загрузки данных для ${basePath || category.type}`;
    errorMessage.style.color = 'red';
    document.querySelector('.content-area').appendChild(errorMessage);
  }
}

// Внутренняя функция для рекурсивной загрузки вложенных данных
async function loadAndDisplayCategoryDataRecursivelyInternal(category, basePath) {
  try {
    // Загружаем index.json для подкатегории
    const response = await fetch(`data/${basePath}/index.json`);
    if (!response.ok) {
      throw new Error(`Не удалось загрузить data/${basePath}/index.json`);
    }
    
    const jsonData = await response.json();
    
    // Создаем таблицу
    const table = document.createElement('table');
    table.className = 'category-table nested';
    table.dataset.type = category.type; // Добавляем атрибут data-type
    table.style.marginLeft = '20px';
    
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
    for (const item of jsonData) {
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
      
      // Добавляем обработчик клика для открытия/закрытия скрытых частей
      row.addEventListener('click', async function(e) {
        e.stopPropagation();
        
        const isLeaf = this.dataset.isLeaf === 'true';
        const fileName = this.dataset.file;
        const currentBasePath = `${basePath}/${fileName}`;
        
        // Находим следующий элемент (детализация)
        let detailRow = this.nextElementSibling;
        
        // Проверяем, существует ли уже строка детализации и является ли она detail
        if (detailRow && detailRow.classList.contains('detail')) {
          // Если строка уже открыта, закрываем её
          if (detailRow.style.display === 'table-row') {
            detailRow.style.display = 'none';
            return;
          } else {
            // Если строка закрыта, открываем её
            detailRow.style.display = 'table-row';
            return;
          }
        } else {
          // Создаем строку детализации
          detailRow = document.createElement('tr');
          detailRow.className = 'detail';
          detailRow.style.display = 'none';
          detailRow.innerHTML = '<td colspan="3"><div class="content">Загрузка...</div></td>';
          
          // Вставляем после текущей строки
          this.parentNode.insertBefore(detailRow, this.nextSibling);
        }
        
        // Если элемент - лист, загружаем содержимое статьи
        if (isLeaf) {
          try {
            const articleContent = await fetch(`data/${currentBasePath}/index.txt`).then(r => r.text());
            detailRow.querySelector('.content').innerHTML = articleContent;
            detailRow.style.display = 'table-row';
          } catch (err) {
            console.error('Ошибка загрузки статьи:', err);
            detailRow.querySelector('.content').textContent = '❌ Ошибка загрузки статьи.';
          }
        } else {
          // Если элемент не лист, рекурсивно загружаем подкатегорию
          try {
            // Рекурсивно вызываем функцию для загрузки вложенной структуры
            const nestedContent = await loadAndDisplayCategoryDataRecursivelyInternal(
              category, 
              currentBasePath
            );
            
            detailRow.querySelector('.content').innerHTML = '';
            detailRow.querySelector('.content').appendChild(nestedContent);
            detailRow.style.display = 'table-row';
          } catch (err) {
            console.error('Ошибка загрузки подкатегории:', err);
            detailRow.querySelector('.content').textContent = '❌ Ошибка загрузки подкатегории.';
          }
        }
      });
      
      tbody.appendChild(row);
    }
    
    table.appendChild(tbody);
    return table;
  } catch (error) {
    console.error(`Ошибка при загрузке данных для ${basePath}:`, error);
    const errorDiv = document.createElement('div');
    errorDiv.textContent = `❌ Ошибка загрузки подкатегории: ${error.message}`;
    errorDiv.style.color = 'red';
    return errorDiv;
  }
}

// Функция для настройки кнопок сворачивания/разворачивания
function setupToggleButtons() {
  // Кнопка для сворачивания/разворачивания боковой панели
  const toggleSidebarBtn = document.getElementById('toggle-sidebar');
  if (toggleSidebarBtn) {
    toggleSidebarBtn.addEventListener('click', () => {
      const sidebar = document.querySelector('.sidebar');
      const container = document.querySelector('.main-container');
      
      sidebar.classList.toggle('hidden');
      container.classList.toggle('sidebar-hidden');
      
      // Поворачиваем кнопку для визуального эффекта
      toggleSidebarBtn.classList.toggle('rotated');
      
      // Изменяем символ на кнопке
      toggleSidebarBtn.textContent = sidebar.classList.contains('hidden') ? '˃' : '˂';
    });
  }
  
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
      toggleThemesBtn.textContent = sidebar.classList.contains('hidden') ? '˅˄' : '˄˅';
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
      
      // Сначала скрываем все строки таблиц
      document.querySelectorAll('.entry').forEach(row => {
        row.style.display = 'none';
        if (row.nextElementSibling && row.nextElementSibling.classList.contains('detail')) {
          row.nextElementSibling.style.display = 'none';
        }
      });
      
      // Проходим по каждой категории
      for (const category of CATEGORIES) {
        // Загружаем JSON для категории
        try {
          const response = await fetch(`data/${category.type}/index.json`);
          if (!response.ok) continue;
          
          const jsonData = await response.json();
          
          // Создаем узел для категории
          const categoryNode = {
            name: category.title,
            type: category.type,
            children: jsonData
          };
          
          // Выполняем рекурсивный поиск
          recursiveSearch(categoryNode, searchTerm, (node) => {
            // Отображаем узел
            showNode(node, category.type);
          });
        } catch (error) {
          console.error(`Ошибка при поиске в категории ${category.type}:`, error);
        }
      }
    });
  }
}

// Проверка совпадения по полям
function matches(node, searchText) {
  const lowerSearchText = searchText.toLowerCase();
  const nodeName = (node.name || '').toLowerCase();
  const nodeCategory = (node.category || '').toLowerCase();
  const nodeUsage = (node.usage || '').toLowerCase();
  
  return (
    nodeName.includes(lowerSearchText) || 
    nodeCategory.includes(lowerSearchText) || 
    nodeUsage.includes(lowerSearchText)
  );
}

// Рекурсивный поиск
async function recursiveSearch(node, searchText, displayCallback) {
  let found = false;
  
  if (!node.children || !Array.isArray(node.children)) {
    return false;
  }
  
  for (const child of node.children) {
    if (child.isLeaf) {
      // Листовой элемент - проверяем по содержимому или полям
      if (matches(child, searchText)) {
        if (displayCallback) displayCallback(child);
        found = true;
      }
    } else {
      // Не лист - рекурсивный вызов
      const childFound = await recursiveSearchInPath(`${node.type || ''}/${child.fileName}`, searchText, displayCallback);
      
      if (childFound) {
        if (displayCallback) displayCallback(child);
        found = true;
      } else {
        // Проверяем поля текущего элемента
        if (matches(child, searchText)) {
          if (displayCallback) displayCallback(child);
          found = true;
        }
      }
    }
  }
  
  return found;
}

// Рекурсивный поиск по пути к файлу
async function recursiveSearchInPath(path, searchText, displayCallback) {
  try {
    const response = await fetch(`data/${path}/index.json`);
    if (!response.ok) return false;
    
    const jsonData = await response.json();
    
    // Создаем узел для текущего пути
    const currentNode = {
      children: jsonData,
      type: path
    };
    
    let found = false;
    
    for (const child of jsonData) {
      if (child.isLeaf) {
        // Листовой элемент - проверяем содержимое
        const contentResponse = await fetch(`data/${path}/${child.fileName}/index.txt`);
        if (contentResponse.ok) {
          const content = await contentResponse.text();
          if (content.toLowerCase().includes(searchText)) {
            // Найдено совпадение в содержимом листа
            if (displayCallback) displayCallback(child);
            found = true;
          }
        } else if (matches(child, searchText)) {
          // Если не удалось загрузить содержимое, проверяем поля
          if (displayCallback) displayCallback(child);
          found = true;
        }
      } else {
        // Не лист - рекурсивный вызов
        const childFound = await recursiveSearchInPath(`${path}/${child.fileName}`, searchText, displayCallback);
        
        if (childFound) {
          if (displayCallback) displayCallback(child);
          found = true;
        } else {
          // Проверяем поля текущего элемента
          if (matches(child, searchText)) {
            if (displayCallback) displayCallback(child);
            found = true;
          }
        }
      }
    }
    
    return found;
  } catch (error) {
    console.error(`Ошибка при поиске в пути ${path}:`, error);
    return false;
  }
}

// Функция для отображения узла в интерфейсе
function showNode(node, categoryType) {
  // Находим соответствующую строку в DOM и отображаем её
  const rows = document.querySelectorAll('.entry');
  
  for (const row of rows) {
    const fileName = row.dataset.file;
    const nameCell = row.cells[0];
    
    // Проверяем, соответствует ли строка узлу
    if ((fileName && fileName === node.fileName) || 
        (nameCell && nameCell.textContent.trim() === node.name)) {
      // Показываем текущую строку
      row.style.display = '';
      
      // Если у строки есть дочерняя detail строка, показываем и её
      const detailRow = row.nextElementSibling;
      if (detailRow && detailRow.classList.contains('detail')) {
        detailRow.style.display = 'table-row';
      }
      
      // Рекурсивно показываем всех родителей
      showParentRows(row);
    }
  }
}

// Функция для отображения родительских строк
function showParentRows(element) {
  // Находим ближайшую таблицу, к которой принадлежит элемент
  const table = element.closest('table');
  
  // Если элемент находится внутри детального представления
  if (table && table.parentNode.closest('tr.detail')) {
    const parentDetailRow = table.parentNode.closest('tr.detail');
    const parentEntry = parentDetailRow.previousElementSibling;
    
    if (parentEntry && parentEntry.classList.contains('entry')) {
      // Показываем родительский элемент
      parentEntry.style.display = '';
      
      // Открываем детальное представление родительского элемента
      parentDetailRow.style.display = 'table-row';
      
      // Рекурсивно вызываем для родительского элемента
      showParentRows(parentEntry);
    }
  }
}
