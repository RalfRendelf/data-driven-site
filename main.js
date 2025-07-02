import { CATEGORIES } from "./categories.js";
import { renderSections, renderEntries } from "./generator.js";
import { initSectionToggle, initDetailLoading, initSearch } from "./navigation.js";

async function fetchCategoryData(type) {
  try {
    const res = await fetch(`data/${type}/index.json`);
    return await res.json();
  } catch {
    console.error(`Не удалось загрузить data/${type}/index.json`);
    return [];
  }
}

document.addEventListener("DOMContentLoaded", async () => {
  const root = document.getElementById("content");

  // 1) Рендерим секции
  renderSections(root);
  initSectionToggle();

  // 2) Для каждой категории подгружаем свой JSON и рендерим строки
  for (const cat of CATEGORIES) {
    const items = await fetchCategoryData(cat.type);
    renderEntries(items);
  }

  // 3) Навешиваем логику детализации и поиска
  initDetailLoading();
  initSearch();
});
