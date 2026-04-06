// generator.js
import { CATEGORIES } from "./categories.js";


export async function fetchCategoryData(type) {
  try {
    const res = await fetch(`${type}/index.json`);
    return await res.json();
  } catch {
    console.error(`Не удалось загрузить data/${type}/index.json`);
    return [];
  }
}


export function renderSections(root) {
  // Create a container for search results at the top
  const searchResultsSection = document.createElement("section");
  searchResultsSection.id = "search-results";
  searchResultsSection.style.display = "none";
  
  const searchResultsTable = document.createElement("table");
  searchResultsTable.className = "category-table";
  searchResultsTable.innerHTML = `
    <thead>
      <tr><th>Название</th><th>Категория</th><th>Применение</th></tr>
    </thead>
    <tbody id="search-results-body"></tbody>
  `;
  
  searchResultsSection.appendChild(searchResultsTable);
  root.appendChild(searchResultsSection);

  CATEGORIES.forEach(cat => {
    const sec = document.createElement("section");
    sec.innerHTML = `
      <h1 class="category-header">${cat.title}</h1>
      <table class="category-table" data-type="${cat.type}" style="display:none">
        <thead>
          <tr>${cat.columns.map(h=>`<th>${h}</th>`).join("")}</tr>
        </thead>
        <tbody id="${cat.type}-body"></tbody>
      </table>
    `;
    root.appendChild(sec);
  });
}

export async function renderEntries(items, basePath = '') {
  // Обрабатываем каждый элемент
  for (const item of items) {
    // Находим нужную таблицу по типу
    const tbody = document.getElementById(`${item.type}-body`);
    if (!tbody) continue;

    // Создаём строку
    const tr = document.createElement("tr");
    tr.className = "entry";
    // Сохраняем только имя файла/папки, а не полный путь
    tr.dataset.file = item.fileName;
    tr.dataset.isLeaf = String(item.isLeaf || false);
    
    // Заполняем ячейки в зависимости от структуры item
    tr.innerHTML = `
      <td>${item.name}</td>
      <td>${item.category}</td>
      <td>${item.usage}</td>
    `;

    // Добавляем строку в таблицу
    tbody.appendChild(tr);

    // Добавляем строку деталей
    const detailRow = document.createElement("tr");
    detailRow.className = "detail";
    detailRow.style.display = "none";
    detailRow.innerHTML = `
      <td colspan="3">
        <div class="content">Загрузка...</div>
      </td>
    `;
    tbody.appendChild(detailRow);
    
    // Если это не листовой элемент, загружаем вложенную структуру
    if (!item.isLeaf) {
      // Формируем новый basePath для вложенной папки
      const newBasePath = basePath ? `${basePath}${item.fileName}/` : `data/${item.type}/${item.fileName}/`;
      try {
        const nestedItems = await fetchCategoryDataAtPath(newBasePath);
        if (nestedItems && nestedItems.length > 0) {
          // Рекурсивно вызываем renderEntries для вложенных элементов
          const nestedTable = document.createElement("table");
          nestedTable.className = "category-table nested";
          nestedTable.innerHTML = `
            <thead>
              <tr><th>Название</th><th>Категория</th><th>Описание</th></tr>
            </thead>
            <tbody id="${item.fileName}-nested-body"></tbody>
          `;
          
          // Добавляем вложенные элементы в detail row
          detailRow.querySelector('.content').appendChild(nestedTable);
          
          // Рекурсивно отрисовываем вложенные элементы
          await renderEntries(nestedItems, newBasePath);
        }
      } catch (error) {
        console.error(`Ошибка загрузки вложенных элементов для ${item.fileName}:`, error);
      }
    }
  }
}

// Вспомогательная функция для загрузки данных по указанному пути
async function fetchCategoryDataAtPath(path) {
  try {
    // Убираем "data/" из начала пути и добавляем "index.json" в конце
    const normalizedPath = path.endsWith('/') ? path : path + '/';
    const res = await fetch(`${normalizedPath}index.json`);
    return await res.json();
  } catch {
    console.error(`Не удалось загрузить ${path}index.json`);
    return [];
  }
}

export function loadBlocks(basePath) {
  document.querySelectorAll("tr.entry").forEach(row => {
    row.addEventListener("click", async () => {

      const detail = row.nextElementSibling;
      const isOpen = detail.style.display === "table-row";

      // Закрываем все остальные
      document.querySelectorAll("tr.detail").forEach(d => d.style.display = "none");
      if (isOpen) return;

      detail.style.display = "table-row";
      const div = detail.querySelector(".content");

      if (div.dataset.loaded) return;

      const file = row.dataset.file;
      const isLeaf = row.dataset.isLeaf === "true";

      try {
        if (isLeaf) {
          // -----------------------------
          // ЗАГРУЗКА СТАТЬИ из папки с index.txt
          // -----------------------------
          // For nested content, basePath already contains the full path to the category
          const articlePath = `${basePath}${file}/`;
          
          // Load the main content from index.txt in the article folder
          const txtResponse = await fetch(`${articlePath}index.txt`);
          const txt = await txtResponse.text();
          
          const { loadCodeBlocks } = await import("./generator.js");
          const processed = await loadCodeBlocks(txt, articlePath);

          div.innerHTML = processed;

        } else {
          // -----------------------------
          // ЗАГРУЗКА ПОДКАТЕГОРИИ (index.json)
          // -----------------------------
          const newBase = `${basePath}${file}/`;
          const json = await fetch(`${newBase}index.json`).then(r => r.json());

          const nested = document.createElement("table");
          nested.className = "category-table nested";

          nested.innerHTML = `
            <thead>
              <tr><th>Название</th><th>Категория</th><th>Описание</th></tr>
            </thead>
            <tbody>
              ${json.map(i => `
                <tr class="entry"
                    data-file="${i.fileName}"
                    data-is-leaf="${i.isLeaf}">
                  <td>${i.name}</td>
                  <td>${i.category}</td>
                  <td>${i.usage}</td>
                </tr>
                <tr class="detail" style="display:none">
                  <td colspan="3"><div class="content">Загрузка...</div></td>
                </tr>
              `).join("")}
            </tbody>
          `;

          div.innerHTML = "";
          div.appendChild(nested);

          // Рекурсивно навешиваем обработчики для новой папки
          loadBlocks(newBase);
        }

        div.dataset.loaded = "true";

      } catch (e) {
        console.error(e);
        div.textContent = "❌ Ошибка загрузки.";
      }
    });
  });
}




// Функция для загрузки блоков кода из отдельных файлов и вставки в HTML
export async function loadCodeBlocks(contentHtml, basePath) {
  // 1. Если есть маркер окончания — обрезаем всё после него
  const endMarker = "</file_content>";
  const endIndex = contentHtml.indexOf(endMarker);
  if (endIndex !== -1) {
    contentHtml = contentHtml.substring(0, endIndex);
  }

  // 2. Ищем блоки вида <pre><code>имя_файла.txt</code></pre> и заменяем их содержимым
  const regex = /<pre><code>\s*([^<>\s]+\.txt)\s*<\/code><\/pre>/gi;
  
  let result = contentHtml;
  
  // Используем replace с асинхронной IIFE, чтобы дождаться загрузки всех файлов
  const matches = [...contentHtml.matchAll(regex)];
  
  for (const match of matches) {
    const fullMatch = match[0];
    const fileName = match[1];
    
    try {
      // 3. Загружаем содержимое файла из текущей директории (basePath + fileName)
      const response = await fetch(`${basePath}${fileName}`);
      let code = await response.text();

      // 4. Экранируем < и >
      code = code
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;");

      // 5. Формируем итоговый HTML-блок
      const replaced = `
<pre><code class="cpp">
${code}
</code></pre>`;

      // 6. Заменяем вставку на реальный код
      result = result.replace(fullMatch, replaced);

    } catch (error) {
      console.error(`Ошибка загрузки кода из ${fileName}:`, error);

      const replaced = `
<pre><code class="cpp">
// Ошибка загрузки файла: ${fileName}
</code></pre>`;

      result = result.replace(fullMatch, replaced);
    }
  }

  return result;
}

// Async function to load article content from index.txt within a folder
export async function loadArticleContent(fileName, type) {
  // Construct the path to the article folder
  // If type is provided, use the standard structure: data/type/filename/
  // If type is empty, fileName contains the full path to the folder
  let articlePath;
  if (type && type.length > 0) {
    articlePath = `data/${type}/${fileName}/`;
  } else {
    // In this case, fileName already contains the full path
    articlePath = `${fileName}/`;
  }
  
  try {
    // Load the main content from index.txt in the article folder
    const response = await fetch(`${articlePath}index.txt`);
    const content = await response.text();
    
    // Process any code blocks in the content using the updated loadCodeBlocks function
    const processed = await loadCodeBlocks(content, articlePath);
    
    return processed;
  } catch (error) {
    console.error(`Ошибка загрузки статьи из ${fileName}:`, error);
    return "❌ Ошибка загрузки содержимого статьи.";
  }
}
