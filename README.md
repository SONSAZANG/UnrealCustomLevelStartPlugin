# 🎮 LevelSelector - Unreal Engine Editor Plugin

에디터 툴바에 드롭다운으로 레벨을 선택하고, 버튼 클릭 한 번으로 해당 레벨을 실행할 수 있는 UE 플러그인입니다.

![Image](https://github.com/user-attachments/assets/a8ea5621-d5b4-4135-959f-730b0fe58846)

---

## 🧩 기능 요약

- 툴바에 **레벨 선택 드롭다운** 추가
- 선택된 레벨을 에디터 뷰포트에서 **즉시 Play**
- 직관적이고 심플한 워크플로우

---

## 🖥️ 사용 예시

### 1. 에디터 툴바에 드롭다운 추가됨
<img width="368" alt="Image" src="https://github.com/user-attachments/assets/5d1301f1-f931-4b79-bfbc-d6704558f8e2" />

### 2. "Play Level" 버튼 클릭 시 선택된 레벨 실행
<img width="256" alt="Image" src="https://github.com/user-attachments/assets/2001e84e-8ccf-459a-9232-a3e57b21f95c" />
---

## 🛠️ 설치 및 설정
### 1. 플러그인 설치 Plugins 폴더에 복사
https://drive.google.com/drive/folders/1gcyKnJf0xdnLCAhqgKs6I4DUk2O8l4fY?usp=drive_link
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
