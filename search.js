import { CATEGORIES } from "./categories.js";
// Функция для настройки глобального поиска по всему дереву
export function setupGlobalSearch() {
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
  path: category.type,
  children: jsonData
};

          
          // Выполняем рекурсивный поиск
          recursiveSearch(categoryNode, searchTerm, (node, child) => {
    showNode(child);
    showNode(node); // родитель
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
        if (displayCallback) displayCallback(node, child);

        found = true;
      }
    } else {
      // Не лист - рекурсивный вызов
     const base = node.path || node.type || '';
const childPath = `${base}/${child.fileName}`;

const childFound = await recursiveSearchInPath(childPath, searchText, displayCallback);

      
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
