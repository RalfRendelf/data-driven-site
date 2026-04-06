export function initSectionToggle() {
    document.querySelectorAll(".category-header").forEach(h => {
      h.style.cursor = "pointer";
      h.addEventListener("click", () => {
        const tbl = h.nextElementSibling;
        tbl.style.display = tbl.style.display === "none" ? "table" : "none";
      });
    });
  }
  
  // export function initDetailLoading() {
  // document.querySelectorAll("tr.entry").forEach(row => {
  //   row.addEventListener("click", async () => {

  //     const detail = row.nextElementSibling;
  //     const isOpen = detail.style.display === "table-row";

  //     // Закрываем все остальные
  //     document.querySelectorAll("tr.detail").forEach(d => d.style.display = "none");
  //     if (isOpen) return;

  //     detail.style.display = "table-row";
  //     const div = detail.querySelector(".content");

  //     if (div.dataset.loaded) return;

  //     // Берём type из родительской таблицы
  //     const table = row.closest("table");
  //     const type = table.dataset.type;

  //     // Get fileName from the dataset instead of text content since now we expect the fileName value
  //     const fileName = row.dataset.file;

  //     const isLeaf = row.dataset.isLeaf === "true";

  //     try {
  //       if (isLeaf) {
  //         // Загрузка статьи из папки, содержащей index.txt и файлы кода
  //         const { loadArticleContent } = await import("./generator.js");
  //         const processed = await loadArticleContent(fileName, type);

  //         div.innerHTML = processed;

  //       } else {
  //         // Загрузка подкатегории
  //         const json = await fetch(`data/${type}/${fileName}/index.json`).then(r => r.json());

  //         const table = document.createElement("table");
  //         table.className = "category-table nested";

  //         table.innerHTML = `
  //           <thead>
  //             <tr><th>Название</th><th>Категория</th><th>Описание</th></tr>
  //           </thead>
  //           <tbody>
  //             ${json.map(i => `
  //               <tr class="entry" data-file="${i.fileName}" data-is-leaf="${i.isLeaf}">
  //                 <td>${i.name}</td>
  //                 <td>${i.category}</td>
  //                 <td>${i.usage}</td>
  //               </tr>
  //               <tr class="detail" style="display:none">
  //                 <td colspan="3"><div class="content">Загрузка...</div></td>
  //               </tr>
  //             `).join("")}
  //           </tbody>
  //         `;

  //         div.innerHTML = "";
  //         div.appendChild(table);

  //         // Рекурсивно навешиваем обработчики
  //         initDetailLoading();
  //       }

  //       div.dataset.loaded = "true";

  //     } catch (e) {
  //       console.error(e);
  //       div.textContent = "❌ Ошибка загрузки.";
  //     }
  //   });
  // });}
  // function addCodeVisibilityControls(container) {
  //   // Находим все блоки кода
  //   const codeBlocks = container.querySelectorAll('pre');
    
  //   codeBlocks.forEach(block => {
  //     // Создаем обертку для блока кода
  //     const wrapper = document.createElement('div');
  //     wrapper.className = 'code-container code-hidden';
      
  //     // Создаем кнопку для переключения видимости
  //     const toggleBtn = document.createElement('button');
  //     toggleBtn.className = 'show-code-btn';
  //     toggleBtn.type = 'button';
      
  //     // Вставляем кнопку перед блоком кода
  //     block.parentNode.insertBefore(wrapper, block);
  //     wrapper.appendChild(toggleBtn);
  //     wrapper.appendChild(block);
      
  //     // Добавляем обработчик событий для кнопки
  //     toggleBtn.addEventListener('click', function(e) {
  //       e.stopPropagation();
  //       const isHidden = wrapper.classList.contains('code-hidden');
        
  //       if (isHidden) {
  //         wrapper.classList.remove('code-hidden');
  //         wrapper.classList.add('code-visible');
  //       } else {
  //         wrapper.classList.remove('code-visible');
  //         wrapper.classList.add('code-hidden');
  //       }
  //     });
  //   });
  // }

  export function initDetailLoading() {
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

      // Берём type из родительской таблицы
      const table = row.closest("table");
      const type = table.dataset.type;

      // Get fileName from the dataset instead of text content since now we expect the fileName value
      const fileName = row.dataset.file;

      const isLeaf = row.dataset.isLeaf === "true";

      try {
        if (isLeaf) {
          // Загрузка статьи из папки, содержащей index.txt и файлы кода
          const { loadArticleContent } = await import("./generator.js");
          const processed = await loadArticleContent(fileName, type);

          div.innerHTML = processed;

        } else {
          // Загрузка подкатегории
          const json = await fetch(`data/${type}/${fileName}/index.json`).then(r => r.json());

          const table = document.createElement("table");
          table.className = "category-table nested";

          table.innerHTML = `
            <thead>
              <tr><th>Название</th><th>Категория</th><th>Описание</th></tr>
            </thead>
            <tbody>
              ${json.map(i => `
                <tr class="entry" data-file="${i.fileName}" data-is-leaf="${i.isLeaf}">
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

          // Рекурсивно навешиваем обработчики
          initDetailLoading();
        }

        div.dataset.loaded = "true";

        // После загрузки контента добавляем кнопки для переключения видимости кода
        addCodeVisibilityControls(div);

      } catch (e) {
        console.error(e);
        div.textContent = "❌ Ошибка загрузки.";
      }
    });
  });
}

// Функция для добавления кнопок переключения видимости кода
function addCodeVisibilityControls(container) {
  // Находим все блоки кода
  const codeBlocks = container.querySelectorAll('pre, code');
  
  codeBlocks.forEach(block => {
    // Проверяем, есть ли у блока уже обертка
    if (block.parentElement.classList.contains('code-container')) {
      return;
    }
    
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