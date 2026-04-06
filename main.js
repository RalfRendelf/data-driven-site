import { CATEGORIES } from "./categories.js";
import { generateTreeStructure, logTreeStructure } from "./generator.js";

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
        }
      });
    });
  }
  
  // Генерируем древовидную структуру
  await generateTreeStructure();
  
  // Логируем сформированную структуру для проверки
  logTreeStructure();
});