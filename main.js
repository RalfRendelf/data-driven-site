import { CATEGORIES } from "./categories.js";

// =========================
// 1. ИНИЦИАЛИЗАЦИЯ ПРИ ЗАГРУЗКЕ
// =========================

document.addEventListener("DOMContentLoaded", async () => {
  initCategorySidebar();
  initCategoryNavigation();
  setupToggleButtons();
  setupGlobalSearch();
});


// =========================
// 2. РЕНДЕР БОКОВОЙ ПАНЕЛИ
// =========================

function initCategorySidebar() {
  const navElement = document.getElementById("categories-nav");
  if (!navElement) return;

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
}


// =========================
// 3. НАВИГАЦИЯ ПО КАТЕГОРИЯМ
// =========================

function initCategoryNavigation() {
  document.querySelectorAll('#categories-nav a').forEach(link => {
    link.addEventListener('click', function(e) {
      e.preventDefault();

      const isActive = this.classList.contains('active');

      document.querySelectorAll('#categories-nav a')
        .forEach(a => a.classList.remove('active'));

      if (!isActive) {
        this.classList.add('active');
        const categoryType = this.getAttribute('data-category');
        displayTreeForCategory(categoryType);
      }
    });
  });
}


// =========================
// 4. МОДАЛЬНОЕ ОКНО ДЛЯ СТАТЕЙ
// =========================

function openArticlePopup(content) {
  const modal = document.getElementById("article-modal");
  const body = modal.querySelector(".modal-body");

  body.innerHTML = content;
  modal.classList.remove("hidden");
}

function closeArticlePopup() {
  const modal = document.getElementById("article-modal");
  modal.classList.add("hidden");
}

document.addEventListener("click", (e) => {
  if (e.target.classList.contains("modal-close")) {
    closeArticlePopup();
  }
  if (e.target.id === "article-modal") {
    closeArticlePopup();
  }
});


// =========================
// 5. ОТОБРАЖЕНИЕ ДЕРЕВА КАТЕГОРИИ
// =========================

export function displayTreeForCategory(categoryType) {
  const category = CATEGORIES.find(cat => cat.type === categoryType);
  if (!category) {
    console.error(`Категория с типом ${categoryType} не найдена`);
    return;
  }

  const contentArea = document.querySelector('.content-area');
  contentArea.innerHTML = '';

  const header = document.createElement('h2');
  header.textContent = category.title;
  contentArea.appendChild(header);

  loadAndDisplayCategoryDataRecursively(category).then(table => {
    if (table) {
      contentArea.appendChild(table);
    }
  });
}


// =========================
// 6. РЕКУРСИВНАЯ ЗАГРУЗКА index.json
// =========================

async function loadAndDisplayCategoryDataRecursively(category, basePath = null) {
  try {
    const path = basePath ? `data/${basePath}/index.json` : `data/${category.type}/index.json`;

    const response = await fetch(path);
    if (!response.ok) throw new Error(`Не удалось загрузить ${path}`);

    const jsonData = await response.json();

    const table = document.createElement('table');
    table.className = basePath ? 'category-table nested' : 'category-table';

    if (!basePath) table.dataset.type = category.type;
    table.style.marginLeft = basePath ? '20px' : '0';

    const thead = document.createElement('thead');
    const headerRow = document.createElement('tr');

    category.columns.forEach(col => {
      const th = document.createElement('th');
      th.textContent = col;
      headerRow.appendChild(th);
    });

    thead.appendChild(headerRow);
    table.appendChild(thead);

    const tbody = document.createElement('tbody');

    for (const item of jsonData) {
      const row = document.createElement('tr');
      row.className = 'entry';
      row.dataset.file = item.fileName;
      row.dataset.isLeaf = item.isLeaf || false;

      const nameCell = document.createElement('td');
      nameCell.textContent = item.name;
      row.appendChild(nameCell);

      const categoryCell = document.createElement('td');
      categoryCell.textContent = item.category;
      row.appendChild(categoryCell);

      const usageCell = document.createElement('td');
      usageCell.textContent = item.usage;
      row.appendChild(usageCell);

      row.addEventListener('click', async function(e) {
        e.stopPropagation();

        const isLeaf = this.dataset.isLeaf === 'true';
        const fileName = this.dataset.file;
        const currentBasePath = basePath ? `${basePath}/${fileName}` : `${category.type}/${fileName}`;

        if (isLeaf) {
          try {
            const rawContent = await fetch(`data/${currentBasePath}/index.txt`).then(r => r.text());

            // 1) Преобразуем <pre><code>...</code></pre> в .code-loader
            const articleContent = transformCodePlaceholders(rawContent);

            // 2) Открываем модалку с уже преобразованным HTML
            openArticlePopup(articleContent);

            // 3) Вешаем обработчики на .code-loader
            const modalBody = document.querySelector(".modal-body");
            setupCodeLoaders(modalBody, currentBasePath);


          } catch (err) {
            openArticlePopup("❌ Ошибка загрузки статьи.");
          }
          return;
        }

        let detailRow = this.nextElementSibling;

        if (detailRow && detailRow.classList.contains('detail')) {
          detailRow.style.display = detailRow.style.display === 'table-row' ? 'none' : 'table-row';
          return;
        }

        detailRow = document.createElement('tr');
        detailRow.className = 'detail';
        detailRow.style.display = 'none';
        detailRow.innerHTML = '<td colspan="3"><div class="content">Загрузка...</div></td>';
        this.parentNode.insertBefore(detailRow, this.nextSibling);

        try {
          const nestedContent = await loadAndDisplayCategoryDataRecursivelyInternal(category, currentBasePath);
          detailRow.querySelector('.content').innerHTML = '';
          detailRow.querySelector('.content').appendChild(nestedContent);
          detailRow.style.display = 'table-row';
        } catch (err) {
          detailRow.querySelector('.content').textContent = '❌ Ошибка загрузки подкатегории.';
        }
      });

      tbody.appendChild(row);
    }

    table.appendChild(tbody);
    return table;

  } catch (error) {
    console.error(`Ошибка при загрузке данных:`, error);
    const errorMessage = document.createElement('p');
    errorMessage.textContent = `Ошибка загрузки данных для ${basePath || category.type}`;
    errorMessage.style.color = 'red';
    document.querySelector('.content-area').appendChild(errorMessage);
  }
}


// =========================
// 7. РЕКУРСИЯ ДЛЯ ВНУТРЕННИХ ПАПОК
// =========================

async function loadAndDisplayCategoryDataRecursivelyInternal(category, basePath) {
  try {
    const response = await fetch(`data/${basePath}/index.json`);
    if (!response.ok) throw new Error(`Не удалось загрузить data/${basePath}/index.json`);

    const jsonData = await response.json();

    const table = document.createElement('table');
    table.className = 'category-table nested';
    table.dataset.type = category.type;
    table.style.marginLeft = '20px';

    const thead = document.createElement('thead');
    const headerRow = document.createElement('tr');

    category.columns.forEach(col => {
      const th = document.createElement('th');
      th.textContent = col;
      headerRow.appendChild(th);
    });

    thead.appendChild(headerRow);
    table.appendChild(thead);

    const tbody = document.createElement('tbody');

    for (const item of jsonData) {
      const row = document.createElement('tr');
      row.className = 'entry';
      row.dataset.file = item.fileName;
      row.dataset.isLeaf = item.isLeaf || false;

      const nameCell = document.createElement('td');
      nameCell.textContent = item.name;
      row.appendChild(nameCell);

      const categoryCell = document.createElement('td');
      categoryCell.textContent = item.category;
      row.appendChild(categoryCell);

      const usageCell = document.createElement('td');
      usageCell.textContent = item.usage;
      row.appendChild(usageCell);

      row.addEventListener('click', async function(e) {
        e.stopPropagation();

        const isLeaf = this.dataset.isLeaf === 'true';
        const fileName = this.dataset.file;
        const currentBasePath = `${basePath}/${fileName}`;

        if (isLeaf) {
          try {
            const rawContent = await fetch(`data/${currentBasePath}/index.txt`).then(r => r.text());

            // 1) Преобразуем <pre><code>...</code></pre> в .code-loader
            const articleContent = transformCodePlaceholders(rawContent);

            // 2) Открываем модалку с уже преобразованным HTML
            openArticlePopup(articleContent);

            // 3) Вешаем обработчики на .code-loader
            const modalBody = document.querySelector(".modal-body");
            setupCodeLoaders(modalBody, currentBasePath);


          } catch (err) {
            openArticlePopup("❌ Ошибка загрузки статьи.");
          }
          return;
        }

        let detailRow = this.nextElementSibling;

        if (detailRow && detailRow.classList.contains('detail')) {
          detailRow.style.display = detailRow.style.display === 'table-row' ? 'none' : 'table-row';
          return;
        }

        detailRow = document.createElement('tr');
        detailRow.className = 'detail';
        detailRow.style.display = 'none';
        detailRow.innerHTML = '<td colspan="3"><div class="content">Загрузка...</div></td>';
        this.parentNode.insertBefore(detailRow, this.nextSibling);

        try {
          const nestedContent = await loadAndDisplayCategoryDataRecursivelyInternal(category, currentBasePath);
          detailRow.querySelector('.content').innerHTML = '';
          detailRow.querySelector('.content').appendChild(nestedContent);
          detailRow.style.display = 'table-row';
        } catch (err) {
          detailRow.querySelector('.content').textContent = '❌ Ошибка загрузки подкатегории.';
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

function setupCodeLoaders(container, basePath) {
  const loaders = container.querySelectorAll('.code-loader');

  loaders.forEach(loader => {
    const fileName = loader.dataset.file;
    const button = loader.querySelector('.code-toggle');
    const codeBlock = loader.querySelector('.code-block');
    const codeElement = codeBlock.querySelector('code');

    let loaded = false;

    button.addEventListener('click', async () => {
      if (!loaded) {
        try {
          const filePath = `data/${basePath}/${fileName}`;
          const text = await fetch(filePath).then(r => r.text());

          // Экранируем < и >
          const escaped = text
            .replace(/</g, "&lt;")
            .replace(/>/g, "&gt;");

          codeElement.innerHTML = escaped;
          loaded = true;
        } catch (err) {
          codeElement.innerHTML = "Ошибка загрузки файла.";
        }
      }

      codeBlock.classList.toggle('hidden');
      button.textContent = codeBlock.classList.contains('hidden')
        ? "Показать код"
        : "Скрыть код";
    });
  });
}
function transformCodePlaceholders(content) {
  // Ищем блоки:
  // <pre><code>
  // file_name.txt
  // </code></pre>
  const re = /<pre><code>\s*([^<>\r\n]+?)\s*<\/code><\/pre>/g;

  return content.replace(re, (match, fileName) => {
    const safeFileName = fileName.trim();

    return `
      <div class="code-loader" data-file="${safeFileName}">
        <button class="code-toggle">Показать код</button>
        <pre class="code-block hidden"><code></code></pre>
      </div>
    `;
  });
}




// =========================
// 8. ПОИСК (пока пустой)
// =========================

function setupGlobalSearch() {
  // Реализация будет позже
}
