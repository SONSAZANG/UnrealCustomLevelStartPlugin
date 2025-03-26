# 🎮 LevelSelector - Unreal Engine Editor Plugin

에디터 툴바에 드롭다운으로 레벨을 선택하고, 버튼 클릭 한 번으로 해당 레벨을 실행할 수 있는 UE 플러그인입니다.

![LevelSelector Toolbar](./Images/levelselector_toolbar.png)

---

## 🧩 기능 요약

- 툴바에 **레벨 선택 드롭다운** 추가
- 선택된 레벨을 에디터 뷰포트에서 **즉시 Play**
- 직관적이고 심플한 워크플로우

---

## 🖥️ 사용 예시

### 1. 에디터 툴바에 드롭다운 추가됨

![GIF: 드롭다운으로 레벨 선택](./Images/levelselector_dropdown.gif)

### 2. "Play Level" 버튼 클릭 시 선택된 레벨 실행

![GIF: 레벨 실행](./Images/play_selected_level.gif)

---

## 🛠️ 설치 및 설정

### 1. Plugins 폴더에 복사
YourProject/Plugins/LevelSelector/

### 2. `.uproject` 열고 플러그인 활성화  
`Edit > Plugins > Installed > LevelSelector` → 체크 후 에디터 재시작

---

## 📁 기본 구조

```plaintext
LevelSelector/
├── Source/
│   └── LevelSelector/
│       ├── LevelSelector.h
│       ├── LevelSelector.cpp
│       └── ...
├── Resources/
│   └── Icon128.png
└── README.md
