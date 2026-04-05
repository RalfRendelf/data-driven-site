// generator.js
import { CATEGORIES } from "./categories.js";


export async function fetchCategoryData(type) {
  try {
    const res = await fetch(`/${type}/index.json`);
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

export function initDetailLoading() {
  document.querySelectorAll("tr.entry").forEach(row => {
    row.addEventListener("click", async () => {

      const detail = row.nextElementSibling;
      const isOpen = detail.style.display === "table-row";

      document.querySelectorAll("tr.detail").forEach(d => d.style.display = "none");
      if (isOpen) return;

      detail.style.display = "table-row";
      const div = detail.querySelector(".content");

      if (div.dataset.loaded) return;

      // Берём type из родительской таблицы
      const table = row.closest("table");
      const type = table.dataset.type;

      // Берём fileName из первой ячейки строки (или из JSON при генерации)
      const file = row.dataset.file; // можно убрать, если хочешь полностью dataset очистить

      const isLeaf = row.dataset.isLeaf === "true";

      try {
        if (isLeaf) {
          const txt = await fetch(`data/${type}/${file}`).then(r => r.text());
          div.innerHTML = txt;
        } else {
          const json = await fetch(`data/${type}/${file}/index.json`).then(r => r.json());

          const table = document.createElement("table");
          table.className = "category-table nested";

          table.innerHTML = `
            <thead>
              <tr><th>Название</th><th>Категория</th><th>Описание</th></tr>
            </thead>
            <tbody>
              ${json.map(i => `
                <tr class="entry"
                    data-is-leaf="${i.isLeaf}"
                    data-file="${i.fileName}">
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
          div.appendChild(table);

          initDetailLoading();
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

  // 2. Ищем блоки вида <pre><code>имя_файла.txt</code></pre>
  const regex = /<pre><code>\s*([^<>\s]+\.txt)\s*<\/code><\/pre>/gi;
  let match;

  while ((match = regex.exec(contentHtml)) !== null) {
    const fullMatch = match[0];
    const fileName = match[1];

    try {
      // 3. Загружаем содержимое файла
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
      contentHtml = contentHtml.replace(fullMatch, replaced);

    } catch (error) {
      console.error(`Ошибка загрузки кода из ${fileName}:`, error);

      const replaced = `
<pre><code class="cpp">
// Ошибка загрузки файла: ${fileName}
</code></pre>`;

      contentHtml = contentHtml.replace(fullMatch, replaced);
    }
  }

  return contentHtml;
}
