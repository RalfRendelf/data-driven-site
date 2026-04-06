// описываем категории и сразу экспортируем
export const CATEGORIES = [
    {
      title: "📘 Паттерны проектирования",
      type:  "паттерны",
      columns: ["Название", "Тип", "Применяется"]
    },
    {
      title: "📙 Архитектурные паттерны",
      type:  "архитектуры",
      columns: ["Название", "Для чего", "Особенности"]
    },
    {
      title: "🧰 Инструменты и технологии",
      type:  "средства",
      columns: ["Название", "Категория", "Назначение"]
    },
    {
      title: "🔬 Алгоритмы",
      type:  "алгоритмы",
      columns: ["Название", "Категория", "Применение"]
    },
    {
      title: "⚙️ Стандарты C++",
      type:  "стандарты C++",
      columns: ["Название", "Категория", "Описание"]
    },
    {
<<<<<<< HEAD
      title: "🔍 STL (Standard Template Library)",
=======
      title: "🔍C++ и STL (Standard Template Library)",
>>>>>>> a0f816f83ec18c9f49795b86064d3dcbb2a8b80b
      type:  "stl",
      columns: ["Название", "Категория", "Описание"]
    },
    {
      title: "🔍 Микроконтроллеры ",
      type:  "микроконтроллеры",
      columns: ["Название", "Категория", "Описание"]
<<<<<<< HEAD
=======
    },
    {
      title: "📱 Qt (C++)",
      type: "qt",
      columns: ["Название", "Категория", "Описание"]
    },
    {
      title: "📱 Android (Java)",
      type: "android",
      columns: ["Название", "Категория", "Описание"]
    },
    {
      title: "🚀 Boost C++",
      type: "boost",
      columns: ["Название", "Категория", "Описание"]
>>>>>>> a0f816f83ec18c9f49795b86064d3dcbb2a8b80b
    }
    
  ];
  console.log("categories.js загружен", CATEGORIES);