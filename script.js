document.addEventListener("DOMContentLoaded", async () => {
  const content = document.getElementById("content");
  const categories = window.CATEGORIES;

  // 1) Сгенерировать секции и пустые таблицы
  categories.forEach(cat => {
    const section = document.createElement("section");
    section.innerHTML = `
      <h1 class="category-header">${cat.title}</h1>
      <table class="category-table" style="display:none">
        <thead>
          <tr>${cat.columns.map(c => `<th>${c}</th>`).join("")}</tr>
        </thead>
        <tbody id="${cat.type}-body"></tbody>
      </table>
    `;
    content.appendChild(section);
  });

  // 2) Навесить открытие/закрытие секции по клику на заголовок
  document.querySelectorAll(".category-header").forEach(header => {
    header.style.cursor = "pointer";
    header.addEventListener("click", () => {
      const table = header.nextElementSibling;
      table.style.display = table.style.display === "none" ? "table" : "none";
    });
  });

  // 3) Подгрузить список файлов из data/index.json
  let items = [];
  try {
    items = await fetch("data/index.json").then(r => r.json());
  } catch {
    console.error("Не удалось загрузить data/index.json");
  }

  // 4) Заполнить каждую таблицу строками
  items.forEach(item => {
    const tbody = document.getElementById(`${item.type}-body`);
    if (!tbody) return;

    const slug = item.name.toLowerCase().replace(/\s+/g, "_");
    // строка записи
    const entry = document.createElement("tr");
    entry.classList.add("entry");
    entry.dataset.name = item.name;
    entry.dataset.category = item.category;
    entry.dataset.usage = item.usage;
    entry.dataset.file = `${item.type}_${slug}.txt`;
    entry.innerHTML = `
      <td>${item.name}</td>
      <td>${item.category}</td>
      <td>${item.usage}</td>
    `;
    tbody.appendChild(entry);

    // строка детали
    const detail = document.createElement("tr");
    detail.classList.add("detail");
    detail.style.display = "none";
    detail.innerHTML = `
      <td colspan="${item.type === "средства" ? 3 : 3}">
        <div class="content">Загрузка...</div>
      </td>
    `;
    tbody.appendChild(detail);
  });

  // 5) Навесить клик-обработчики на entry для загрузки деталей
  document.querySelectorAll("tr.entry").forEach(row => {
    row.addEventListener("click", async () => {
      const detail = row.nextElementSibling;
      const isOpen = detail.style.display === "table-row";
      // свернуть все
      document.querySelectorAll("tr.detail").forEach(d => d.style.display = "none");
      if (isOpen) return;
      detail.style.display = "table-row";

      const contentDiv = detail.querySelector(".content");
      if (contentDiv.dataset.loaded) return; // уже загружали

      try {
        const file = row.dataset.file;
        const text = await fetch(`data/${file}`).then(r => r.text());
        contentDiv.innerHTML = text;
        contentDiv.dataset.loaded = "true";
      } catch {
        contentDiv.textContent = "❌ Не удалось загрузить содержимое.";
      }
    });
  });

  // 6) Поиск
  const searchBox = document.getElementById("search-box");
  searchBox.addEventListener("input", () => {
    const q = searchBox.value.toLowerCase();
    document.querySelectorAll("tr.entry").forEach(row => {
      const match = ["name", "category", "usage"].some(key =>
        row.dataset[key].toLowerCase().includes(q)
      );
      row.style.display = match ? "" : "none";
      // при фильтрации скрываем детали
      if (row.nextElementSibling?.classList.contains("detail")) {
        row.nextElementSibling.style.display = "none";
      }
    });
  });
});
