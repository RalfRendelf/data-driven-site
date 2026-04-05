// generator.js
import { CATEGORIES } from "./categories.js";

export function renderSections(root) {
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

export function renderEntries(items) {
  items.forEach(item => {
    const tbody = document.getElementById(`${item.type}-body`);
    if (!tbody) return;

    // Используем fileName, если он определен, иначе генерируем из name как раньше
    const fileName = item.type + "/" + item.fileName;
    // || `${item.type}/${item.type}_${item.name.toLowerCase().replace(/\s+/g, "_")}.txt`; 
    
    const entry = document.createElement("tr");
    entry.classList.add("entry");
    entry.dataset.file = fileName;
    entry.dataset.name = item.name;
    entry.dataset.category = item.category;
    entry.dataset.usage = item.usage;
    entry.innerHTML = `
      <td>${item.name}</td>
      <td>${item.category}</td>
      <td>${item.usage}</td>
    `;
    tbody.appendChild(entry);

    const detail = document.createElement("tr");
    detail.classList.add("detail");
    detail.style.display = "none";
    detail.innerHTML = `<td colspan="3"><div class="content">Загрузка...</div></td>`;
    tbody.appendChild(detail);
  });
}