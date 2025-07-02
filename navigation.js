export function initSectionToggle() {
    document.querySelectorAll(".category-header").forEach(h => {
      h.style.cursor = "pointer";
      h.addEventListener("click", () => {
        const tbl = h.nextElementSibling;
        tbl.style.display = tbl.style.display === "none" ? "table" : "none";
      });
    });
  }
  
  export function initDetailLoading() {
    document.querySelectorAll("tr.entry").forEach(row => {
      row.addEventListener("click", async () => {
        const detail = row.nextElementSibling;
        const open   = detail.style.display === "table-row";
        document.querySelectorAll("tr.detail").forEach(d => d.style.display = "none");
        if (open) return;
  
        detail.style.display = "table-row";
        const div = detail.querySelector(".content");
        if (div.dataset.loaded) return;
  
        try {
          const txt = await fetch(`data/${row.dataset.file}`).then(r => r.text());
          div.innerHTML = txt;
          div.dataset.loaded = "true";
        } catch {
          div.textContent = "❌ Ошибка загрузки.";
        }
      });
    });
  }
  
  export function initSearch() {
    const search = document.getElementById("search-box");
    search.addEventListener("input", () => {
      const q = search.value.toLowerCase();
      document.querySelectorAll("tr.entry").forEach(row => {
        const match = ["name","category","usage"].some(key =>
          row.dataset[key].toLowerCase().includes(q)
        );
        row.style.display = match ? "" : "none";
        if (row.nextElementSibling.classList.contains("detail"))
          row.nextElementSibling.style.display = "none";
      });
    });
  }
  