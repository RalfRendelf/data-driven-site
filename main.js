import { CATEGORIES } from "./categories.js";
import { generateTreeStructure } from "./generator.js";
import { displayTreeForCategory } from "./tree.js";
import { setupToggleButtons } from "./navigation.js";
import { setupGlobalSearch } from "./search.js";

document.addEventListener("DOMContentLoaded", async () => {
  // Заполняем боковую панель категориями
  const navElement = document.getElementById("categories-nav");
  if (navElement) {
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
    
    // Добавляем обработчик кликов по категориям
    document.querySelectorAll('#categories-nav a').forEach(link => {
      link.addEventListener('click', function(e) {
        e.preventDefault();
        
        // Проверяем, есть ли у текущей ссылки класс active
        const isActive = this.classList.contains('active');
        
        // Убираем активный класс со всех ссылок
        document.querySelectorAll('#categories-nav a').forEach(a => {
          a.classList.remove('active');
        });
        
        // Если текущая ссылка не была активной, добавляем ей класс active
        if (!isActive) {
          this.classList.add('active');
          
          // Получаем тип категории
          const categoryType = this.getAttribute('data-category');
          
          // Отображаем дерево для выбранной категории
          displayTreeForCategory(categoryType);
        }
      });
    });
  }
  
  // Генерируем древовидную структуру
  const treeContainer = await generateTreeStructure();
  
  // Добавляем атрибут data-type к таблицам для отслеживания типа категории
  // if (treeContainer) {
  //   CATEGORIES.forEach(category => {
  //     const table = treeContainer.querySelector(`.category-table`);
  //     if (table) {
  //       table.dataset.type = category.type;
  //     }
  //   });
  // }
  
  // Добавляем функциональность для кнопок сворачивания
  setupToggleButtons();
  // document.addEventListener('DOMContentLoaded', setupToggleButtons);
  // Добавляем функциональность поиска
  setupGlobalSearch();
});



