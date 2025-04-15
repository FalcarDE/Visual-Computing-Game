# 🎮 Visual Computing Game

Willkommen zum Visual Computing Projekt, entwickelt mit **Visual Studio 2022**.  
Dieses Spiel ist Teil einer Lehrveranstaltung im Bereich Visual Computing.

---

## 🛠️ Ausführungshinweis für Prof. Sahm

📌 *Das Spiel wurde ausschließlich im **Debug-Modus** entwickelt und getestet. Bitte stellen Sie sicher, dass alle Abhängigkeiten korrekt eingebunden sind, wenn die `.exe` ausgeführt wird. Local konnte ich es bei mir ausführen.*  

👉 [source/code/build/win64/game/Debug/game_debug.exe](source/code/build/win64/game/Debug/game_debug.exe)

Der **Release-Modus** wurde lediglich einmalig für einen kurzen Test kompiliert, jedoch nicht weiter verfolgt oder regelmäßig verwendet.  

---

## 📦 Abhängigkeiten

### 🔹 SFML (Simple and Fast Multimedia Library)
- SFML wird im Projekt verwendet, ist jedoch **nicht Teil dieses Repositories**.
- Die Bibliothek wurde **lokal eingebunden** und muss manuell heruntergeladen und verlinkt werden.
- Download: [SFML-2.5.1-windows-vc15-64-bit](https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip)

### 🔹 tinyxml2
- tinyxml2 wird für XML-Verarbeitung verwendet.
- Die Bibliothek wurde mittels **[vcpkg](https://github.com/microsoft/vcpkg)** eingebunden.
- Installationsbefehl (wenn vcpkg bereits eingerichtet ist):
  ```bash
  vcpkg install tinyxml2
---

## 🎯 Bugs

In dieser Sektion werden Probleme aufgeführt, die sich speziell auf Game beziehen.

---