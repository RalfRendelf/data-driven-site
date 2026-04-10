// import { loadArticleContent } from './generator.js';

// export function initSectionToggle() {
//   document.querySelectorAll(".category-header").forEach(h => {
//     h.style.cursor = "pointer";
//     h.addEventListener("click", () => {
//       const tbl = h.nextElementSibling;
//       tbl.style.display = tbl.style.display === "none" ? "table" : "none";
//     });
//   });
// }

// export function initDetailLoading() {
//   document.querySelectorAll("tr.entry").forEach(row => {
//     row.addEventListener("click", async () => {

//       const detail = row.nextElementSibling;
//       const isOpen = detail.style.display === "table-row";

//       // Закрываем все остальные
//       document.querySelectorAll("tr.detail").forEach(d => d.style.display = "none");
//       if (isOpen) return;

//       detail.style.display = "table-row";
//       const div = detail.querySelector(".content");

//       if (div.dataset.loaded) return;

//       // Берём type из родительской таблицы
//       const table = row.closest("table");
//       const type = table.dataset.type;

//       // Get fileName from the dataset instead of text content since now we expect the fileName value
//       const fileName = row.dataset.file;

//       const isLeaf = row.dataset.isLeaf === "true";

//       try {
//         if (isLeaf) {
//           // Загрузка статьи из папки, содержащей index.txt и файлы кода
//           const processed = await loadArticleContent(fileName, type);

//           div.innerHTML = processed;

//         } else {
//           // Загрузка подкатегории
//           const json = await fetch(`data/${type}/${fileName}/index.json`).then(r => r.json());

//           const table = document.createElement("table");
//           table.className = "category-table nested";

//           table.innerHTML = `
//             <thead>
//               <tr><th>Название</th><th>Категория</th><th>Описание</th></tr>
//             </thead>
//             <tbody>
//               ${json.map(i => `
//                 <tr class="entry" data-file="${i.fileName}" data-is-leaf="${i.isLeaf}">
//                   <td>${i.name}</td>
//                   <td>${i.category}</td>
//                   <td>${i.usage}</td>
//                 </tr>
//                 <tr class="detail" style="display:none">
//                   <td colspan="3"><div class="content">Загрузка...</div></td>
//                 </tr>
//               `).join("")}
//             </tbody>
//           `;

//           div.innerHTML = "";
//           div.appendChild(table);

//           // Рекурсивно навешиваем обработчики
//           initDetailLoading();
//         }

//         div.dataset.loaded = "true";

//         // После загрузки контента добавляем кнопки для переключения видимости кода
//         addCodeVisibilityControls(div);

//       } catch (e) {
//         console.error(e);
//         div.textContent = "❌ Ошибка загрузки.";
//       }
//     });
//   });
// }

// // Функция для добавления кнопок переключения видимости кода
// function addCodeVisibilityControls(container) {
//   // Находим все блоки кода
//   const codeBlocks = container.querySelectorAll('pre, code');
  
//   codeBlocks.forEach(block => {
//     // Проверяем, есть ли у блока уже обертка
//     if (block.parentElement.classList.contains('code-container')) {
//       return;
//     }
    
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

// export function initSearch() {
//   const search = document.getElementById("search-box");
//   search.addEventListener("input", () => {
//     const q = search.value.toLowerCase();
    
//     if (q === "") {
//       // Если поисковый запрос пуст, восстанавливаем обычную структуру
//       document.querySelectorAll("tr.entry").forEach(row => {
//         row.style.display = "";
//         if (row.nextElementSibling.classList.contains("detail"))
//           row.nextElementSibling.style.display = "none";
//       });
      
//       // Показываем все заголовки и таблицы
//       document.querySelectorAll(".category-header, .category-table").forEach(el => {
//         el.style.display = "";
//       });
//     } else {
//       // Если есть поисковый запрос, показываем все совпадения
//       document.querySelectorAll("tr.entry").forEach(row => {
//         const match = ["name","category","usage"].some(key =>
//           row.dataset[key].toLowerCase().includes(q)
//         );
//         row.style.display = match ? "" : "none";
//         if (row.nextElementSibling.classList.contains("detail"))
//           row.nextElementSibling.style.display = "none";
//       });
//     }
//   });
// }

// export function initSearch() {
//   const search = document.getElementById("search-box");
//   search.addEventListener("input", async () => {
//     const q = search.value.toLowerCase();
    
//     if (q === "") {
//       // Если поисковый запрос пуст, восстанавливаем обычную структуру
//       document.querySelectorAll(".tree-node").forEach(node => {
//         node.style.display = "";
//         const content = node.querySelector(".tree-content");
//         if (content && content.classList.contains("open")) {
//           content.style.display = "";
//         }
//       });
//     } else {
//       // Если есть поисковый запрос, показываем только совпадения
//       document.querySelectorAll(".tree-node").forEach(node => {
//         const label = node.querySelector('.node-label');
//         if (label) {
//           const text = label.textContent.toLowerCase();
//           const match = text.includes(q);
//           node.style.display = match ? "" : "none";
          
//           // Если узел совпадает, открываем всю цепочку родителей
//           if (match) {
//             let parent = node.parentElement;
//             while (parent && !parent.matches('body')) {
//               if (parent.classList.contains('tree-nested')) {
//                 const treeNode = parent.parentElement.closest('.tree-node');
//                 if (treeNode) {
//                   treeNode.style.display = '';
//                   treeNode.classList.add('open');
//                   const content = treeNode.querySelector('.tree-content');
//                   if (content) {
//                     content.classList.add('open');
//                   }
//                 }
//               }
//               parent = parent.parentElement;
//             }
//           }
//         }
//       });
//     }
//   });
// }
export function setupToggleButtons() {

  // Кнопка для скрытия/отображения тем
  const toggleThemesBtn = document.getElementById('toggle-themes');
  if (toggleThemesBtn) {
    toggleThemesBtn.addEventListener('click', () => {
      const sidebar = document.querySelector('.sidebar');
      const container = document.querySelector('.main-container');
      
      sidebar.classList.toggle('hidden');
      container.classList.toggle('themes-hidden');
      
      // Поворачиваем кнопку для визуального эффекта
      toggleThemesBtn.classList.toggle('rotated');
      
      // Изменяем символ на кнопке
      toggleThemesBtn.textContent = sidebar.classList.contains('hidden') ? 'скрыть' : 'показать';
    });
  }
}