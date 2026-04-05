import { CATEGORIES } from "./categories.js";
import { renderSections, renderEntries,fetchCategoryData } from "./generator.js";
import { initSectionToggle, initDetailLoading, initSearch } from "./navigation.js";



document.addEventListener("DOMContentLoaded", async () => {
  const root = document.getElementById("content");

  // 1) Рендерим секции
  renderSections(root);
  initSectionToggle();

  // 2) Для каждой категории подгружаем свой JSON и рендерим строки
  for (const cat of CATEGORIES) {
    const items = await fetchCategoryData(`data/${cat.type}`);
    await renderEntries(items);
  }

  // 3) Навешиваем логику детализации и поиска
  initDetailLoading();
  initSearch();
});