import { CATEGORIES } from "./categories.js";
// Функция для отображения дерева для выбранной категории
export function displayTreeForCategory(categoryType) {
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