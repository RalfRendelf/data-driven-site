import { CATEGORIES } from "./categories.js";

const jsonRoot = {
  data: null,
  isLoaded: false,
  reDraw: true,
  needsDraw: false,
  children: [],
  category: null
};

let lastSearchText = "";

document.addEventListener("DOMContentLoaded", () => {
  initCategorySidebar();
  startRenderLoop();
  initCategoryNavigation();
});

function initCategorySidebar() {
  const navElement = document.getElementById("categories-nav");
  if (!navElement) return;

  navElement.innerHTML = `
    <ul>
      ${CATEGORIES.map(cat => `
        <li>
          <a href="#" data-category="${cat.type}">
            ${cat.title}
          </a>
        </li>
      `).join("")}
    </ul>
  `;
}

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
  if (e.target.classList.contains("modal-close")) closeArticlePopup();
  if (e.target.id === "article-modal") closeArticlePopup();
});

export function displayTreeForCategory(categoryType) {
  const category = CATEGORIES.find(cat => cat.type === categoryType);
  if (!category) return;

  const contentArea = document.querySelector('.content-area');
  contentArea.innerHTML = '';

  const header = document.createElement('h2');
  header.textContent = category.title;
  contentArea.appendChild(header);

  jsonRoot.data = null;
  jsonRoot.children = [];
  jsonRoot.isLoaded = false;
  jsonRoot.needsDraw = true;
  jsonRoot.reDraw = true;

  loadJsonTree(category);
  // if(lastSearchText == "") return;
  lastSearchText = "";
  searchFrame();
}

async function loadJsonTree(category, basePath = null, container = jsonRoot) {
  const rootPath = basePath ?? category.type;

  if (!basePath) {
    container.category = category;
    container.path = rootPath;
  }

  const jsonData = await fetch(`data/${rootPath}/index.json`).then(r => r.json());

  
  container.needsDraw = true;
  container.reDraw = true;
  container.children = [];

  for (const item of jsonData) {
    const itemPath = `${rootPath}/${item.fileName}`;

    const node = {
      data: item,
      isLoaded: true,
      needsDraw: true,
      reDraw: true,
      path: itemPath,
      children: []
    };

    container.children.push(node);

    if (!item.isLeaf) {
      await loadJsonTree(category, itemPath, node);
    }
  }
  container.isLoaded = true;
  return container;
}


function setupCodeLoaders(container, basePath) {
  const loaders = container.querySelectorAll('.code-loader');

  loaders.forEach(loader => {
    let fileName = loader.dataset.file?.trim();
    const validExtensions = ['.txt', '.cpp', '.c', '.py', '.js','.sh'
    ];
if (!fileName || !validExtensions.some(ext => fileName.endsWith(ext))) {
  const btn = loader.querySelector('.code-toggle');
      if (btn) btn.remove(); 

      loader.classList.remove('code-loader'); 
      return;
}
   

    const button = loader.querySelector('.code-toggle');
    const codeBlock = loader.querySelector('.code-block');
    const codeElement = codeBlock.querySelector('code');

    let loaded = false;

    button.addEventListener('click', async () => {
      if (!loaded) {
        try {
          const filePath = `data/${basePath}/${fileName}`;
          const text = await fetch(filePath).then(r => r.text());

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

function startRenderLoop() {
  function loop() {
    searchFrame();
    renderFrame();
    requestAnimationFrame(loop); // ~60 FPS
  }
  requestAnimationFrame(loop);
}
function renderFrame() {
  if (!jsonRoot.isLoaded) return;
  if (!jsonRoot.reDraw) return;

  if (jsonRoot.reDraw) {
    clearRenderedTree();
  }

  const dom = buildHtmlTree(jsonRoot, CATEGORIES[0]); 
  const contentArea = document.querySelector('.content-area');
  contentArea.appendChild(dom);
  jsonRoot.reDraw = false;
}

function buildTreeDom(node) {
  const wrapper = document.createElement('div');
  wrapper.className = 'rendered-tree';

  // node.data — это массив index.json
  if (Array.isArray(node.data)) {
    const table = document.createElement('table');

    for (const item of node.data) {
      const row = document.createElement('tr');
      row.innerHTML = `
        <td>${item.name}</td>
        <td>${item.category}</td>
        <td>${item.usage}</td>
      `;
      table.appendChild(row);
    }

    wrapper.appendChild(table);
  }

  // Рекурсивно строим детей
  for (const child of node.children) {
    const childDom = buildTreeDom(child);
    wrapper.appendChild(childDom);
  }

  return wrapper;
}
function clearRenderedTree() {
  const contentArea = document.querySelector('.content-area');
  if (!contentArea) return;

  // чистим только дерево, не заголовок
  const oldTrees = contentArea.querySelectorAll('.rendered-tree');
  oldTrees.forEach(el => el.remove());
}


function buildHtmlTree(node) {
  const category = jsonRoot.category;

  const wrapper = document.createElement('div');
  wrapper.className = 'rendered-tree';
  if (!node.children || node.children.length === 0) {
    return wrapper;
  }

  const isRoot = node === jsonRoot;
  const table = createTable(category, isRoot);
  table.appendChild(createTableHeader(category));

  const tbody = document.createElement('tbody');

  node.children.forEach(childNode => {

    if (!childNode.needsDraw) return;

    const item = childNode.data;
    const row = createRow(item);

    attachRowHandlersForTree(row, childNode, item);
    tbody.appendChild(row);

    // если есть дети → создаём detail-row
    if (childNode.children && childNode.children.length > 0) {
      const detailRow = document.createElement('tr');
      detailRow.className = 'detail';
      detailRow.style.display = 'none';
      detailRow.innerHTML = '<td colspan="3"><div class="content"></div></td>';
      tbody.appendChild(detailRow);
    }
  });

  table.appendChild(tbody);
  wrapper.appendChild(table);

  return wrapper;
}



function attachRowHandlersForTree(row, node, item) {
  row.addEventListener('click', async function(e) {
    e.stopPropagation();
    if (!node.needsDraw) return;

    const isLeaf = item.isLeaf;
    const path = node.path;

    if (isLeaf) {
      try {
        const rawContent = await fetch(`data/${path}/index.txt`).then(r => r.text());
        const articleContent = transformCodePlaceholders(rawContent);
        openArticlePopup(articleContent);

        const modalBody = document.querySelector(".modal-body");
        setupCodeLoaders(modalBody, path);

      } catch (err) {
        openArticlePopup("❌ Ошибка загрузки статьи.");
      }
      return;
    }

    const detailRow = row.nextElementSibling;

    if (detailRow.style.display === 'table-row') {
      detailRow.style.display = 'none';
      return;
    }

    detailRow.style.display = 'table-row';

    const contentDiv = detailRow.querySelector('.content');
    contentDiv.innerHTML = '';
    if (node.children && node.children.some(c => c.needsDraw)) {
      const childDom = buildHtmlTree(node);
      contentDiv.appendChild(childDom);
    }
  });
}





function createTable(category, isRoot) {
  const table = document.createElement('table');
  table.className = isRoot ? 'category-table' : 'category-table nested';
  table.style.marginLeft = isRoot ? '0' : '20px';
  table.dataset.type = category.type;
  return table;
}
async function loadJson(category, basePath) {
  const path = basePath
    ? `data/${basePath}/index.json`
    : `data/${category.type}/index.json`;

  const response = await fetch(path);
  if (!response.ok) throw new Error(`Не удалось загрузить ${path}`);

  return response.json();
}
function createTableHeader(category) {
  const thead = document.createElement('thead');
  const headerRow = document.createElement('tr');

  category.columns.forEach(col => {
    const th = document.createElement('th');
    th.textContent = col;
    headerRow.appendChild(th);
  });

  thead.appendChild(headerRow);
  return thead;
}
function createRow(item) {
  const row = document.createElement('tr');
  row.className = 'entry';
  row.dataset.file = item.fileName;
  row.dataset.isLeaf = item.isLeaf || false;

  const nameCell = document.createElement('td');
  nameCell.textContent = item.name;

  const categoryCell = document.createElement('td');
  categoryCell.textContent = item.category;

  const usageCell = document.createElement('td');
  usageCell.textContent = item.usage;

  row.appendChild(nameCell);
  row.appendChild(categoryCell);
  row.appendChild(usageCell);

  return row;
}

function searchFrame() {
  const input = document.querySelector('#search-box');
  if (!input) return;
  if(jsonRoot.isLoaded === false) return;
  const text = input.value.trim().toLowerCase();
  if (text === lastSearchText) return;

  lastSearchText = text;
  const found = searchTree(jsonRoot, text);
  jsonRoot.reDraw = true;
}
function searchTree(node, text) {
  if (text === "") {
    markAllVisible(node);
    return true;
  }
  if (node.data && node.children.length === 0) {
    const { name, category, usage } = node.data;
    const match =
      name.toLowerCase().includes(text) ||
      category.toLowerCase().includes(text) ||
      usage.toLowerCase().includes(text);

    node.needsDraw = match;
    return match;
  }

  // если это папка
  let foundInChildren = false;

  for (const child of node.children) {
    const childFound = searchTree(child, text);
    if (childFound) foundInChildren = true;
  }


  if (foundInChildren) {
    node.needsDraw = true;
    return true;
  }

  if (node.data) {
    const { name, category, usage } = node.data;
    const match =
      name.toLowerCase().includes(text) ||
      category.toLowerCase().includes(text) ||
      usage.toLowerCase().includes(text);

    node.needsDraw = match;
    return match;
  }

  node.needsDraw = foundInChildren;
  return foundInChildren;
}
function markAllVisible(node) {
  node.needsDraw = true;
  for (const child of node.children) {
    markAllVisible(child);
  }
}
