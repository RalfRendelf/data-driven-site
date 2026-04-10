// generator.js
import { CATEGORIES } from "./categories.js";


// Функция для получения древовидной структуры из index.json файлов
export async function generateTreeStructure() {
  // Контейнер для хранения всей древовидной структуры
  const treeStructure = {};
  
  // Проходим по каждой категории из CATEGORIES
  for (const category of CATEGORIES) {
    const type = category.type;
    const columns = category.columns;
    try {
      // Загружаем основной index.json для категории
      const response = await fetch(`data/${type}/index.json`);
      if (!response.ok) {
        console.warn(`Не удалось загрузить data/${type}/index.json`);
        continue;
      }
      
      const jsonData = await response.json();
      
      // Формируем структуру для данной категории
      treeStructure[type] = {
        type: type,
        name: category.title, // используем заголовок из CATEGORIES
        columns: columns,
        children: []
      };
      
      // Обрабатываем каждый элемент в JSON
      for (const item of jsonData) {
        const node = await buildNode(item, type);
        treeStructure[type].children.push(node);
      }
    } catch (error) {
      console.error(`Ошибка при обработке категории ${type}:`, error);
    }
  }
  
  return treeStructure;
}

// Рекурсивная функция для построения узлов дерева
async function buildNode(item, parentType) {
  const node = {
    type: item.type,
    name: item.name,
    fileName: item.fileName,
    category: item.category,
    usage: item.usage,
    isLeaf: item.isLeaf || false,
    children: []
  };
  
  // Если узел не является листом, значит он может иметь подтемы
  if (!node.isLeaf) {
    try {
      // Формируем путь к поддиректории
      const subDirPath = `data/${parentType}/${item.fileName}/index.json`;
      const response = await fetch(subDirPath);
      
      if (response.ok) {
        const subItems = await response.json();
        
        // Рекурсивно обрабатываем подэлементы
        for (const subItem of subItems) {
          const childNode = await buildNode(subItem, parentType);
          node.children.push(childNode);
        }
      }
    } catch (error) {
      console.error(`Ошибка при загрузке подэлементов для ${item.fileName}:`, error);
    }
  }
  
  return node;
}

// Функция для отображения сформированной структуры (временно)
export function logTreeStructure() {
  if (window.treeNodesContainer) {
    console.log('Сформированная древовидная структура:');
    console.log(JSON.stringify(window.treeNodesContainer, null, 2));
  } else {
    console.log('Древовидная структура еще не сформирована');
  }
}