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
          
          // После загрузки контента добавляем кнопки для переключения видимости кода
          addCodeVisibilityControls(div);
        } catch {
          div.textContent = "❌ Ошибка загрузки.";
        }
      });
    });
  }
  
  // Функция для добавления кнопок переключения видимости кода
  function addCodeVisibilityControls(container) {
    // Находим все блоки кода
    const codeBlocks = container.querySelectorAll('pre');
    
    codeBlocks.forEach(block => {
      // Создаем обертку для блока кода
      const wrapper = document.createElement('div');
      wrapper.className = 'code-container code-hidden';
      
      // Создаем кнопку для переключения видимости
      const toggleBtn = document.createElement('button');
      toggleBtn.className = 'show-code-btn';
      toggleBtn.type = 'button';
      
      // Вставляем кнопку перед блоком кода
      block.parentNode.insertBefore(wrapper, block);
      wrapper.appendChild(toggleBtn);
      wrapper.appendChild(block);
      
      // Добавляем обработчик событий для кнопки
      toggleBtn.addEventListener('click', function(e) {
        e.stopPropagation();
        const isHidden = wrapper.classList.contains('code-hidden');
        
        if (isHidden) {
          wrapper.classList.remove('code-hidden');
          wrapper.classList.add('code-visible');
        } else {
          wrapper.classList.remove('code-visible');
          wrapper.classList.add('code-hidden');
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