

# 🧩 **8-Puzzle Solver**  

### 🚀 **درباره پروژه**  
این پروژه مجموعه‌ای از الگوریتم‌های مختلف برای حل مسئله **پازل 8** است. از روش‌های ناآگاهانه مانند BFS گرفته تا الگوریتم‌های پیشرفته‌تر مانند **A*** با هیوریستیک‌های متنوع استفاده شده است.  

### ✨ **ویژگی‌ها**  
- 🌟 حل پازل 8 با استفاده از BFS.  
- 🌟 استفاده از الگوریتم **A*** با دو هیوریستیک:  
  - **فاصله منهتن**  
  - **تعداد خانه‌های خارج از مکان درست**  
- 🌟 روش ترکیبی هیوریستیک‌ها برای کارایی بهتر.  
- 🌟 قابلیت شمارش تعداد حالات بررسی‌شده در هر روش.  
- 🌟 مدیریت پازل‌های غیرقابل‌حل.  

---

### 📂 **ساختار پروژه**  

📦 8-puzzle-solver
┣ 📜 BFS FOLDER          #روش نا آگاهانه 
┣ 📜 H1 FOLDER           # روش A*  با هیوریستیک (مجموع فاصله منهتن)  
┣ 📜 H2 FOLDER           # روش  A* با هیوریستیک (چند خانه در مکان درست نیستن) 
┣ 📜 H3 FOLDER           # ترکیب دو هیوریستیک  
┣ 📜 README.md           # توضیحات پروژه  


### 🧪 **نمونه اجرا**  
**ورودی:**  
```
8 6 7  
2 5 4  
3 0 1  
```  

**خروجی:**  
```
پازل در 31 حرکت حل شد!
تعداد حالات جستجو شده: 7767
8 6 7 
2 5 4 
3 _ 1 
-------
8 6 7 
2 5 4 
3 1 _ 
-------
8 6 7 
2 5 _ 
3 1 4 
-------
8 6 _ 
2 5 7 
3 1 4 
-------
8 _ 6 
2 5 7 
3 1 4 
-------
_ 8 6 
2 5 7 
3 1 4 
-------
2 8 6 
_ 5 7 
3 1 4 
-------
2 8 6 
3 5 7 
_ 1 4 
-------
2 8 6 
3 5 7 
1 _ 4 
-------
2 8 6 
3 5 7 
1 4 _ 
-------
2 8 6 
3 5 _ 
1 4 7 
-------
2 8 6 
3 _ 5 
1 4 7 
-------
2 8 6 
_ 3 5 
1 4 7 
-------
2 8 6 
1 3 5 
_ 4 7 
-------
2 8 6 
1 3 5 
4 _ 7 
-------
2 8 6 
1 3 5 
4 7 _ 
-------
2 8 6 
1 3 _ 
4 7 5 
-------
2 8 6 
1 _ 3 
4 7 5 
-------
2 _ 6 
1 8 3 
4 7 5 
-------
2 6 _ 
1 8 3 
4 7 5 
-------
2 6 3 
1 8 _ 
4 7 5 
-------
2 6 3 
1 _ 8 
4 7 5 
-------
2 _ 3 
1 6 8 
4 7 5 
-------
_ 2 3 
1 6 8 
4 7 5 
-------
1 2 3 
_ 6 8 
4 7 5 
-------
1 2 3 
4 6 8 
_ 7 5 
-------
1 2 3 
4 6 8 
7 _ 5 
-------
1 2 3 
4 6 8 
7 5 _ 
-------
1 2 3 
4 6 _ 
7 5 8 
-------
1 2 3 
4 _ 6 
7 5 8 
-------
1 2 3 
4 5 6 
7 _ 8 
-------
1 2 3 
4 5 6 
7 8 _ 

---
```
### 📊 **مقایسه الگوریتم‌ها**  
| **روش**              | **حالت‌های بررسی‌شده** | **تعداد حرکات** | **سرعت**   |  
|-----------------------|------------------------|------------------|------------|  
| BFS                  | 181440            | 31               | کند        |  
| A* (منهتن)          | 7767                    | 31               | سریع       |  
| A* (ترکیبی)          | 7572                    | 31               | خیلی سریع  |  

---

### 📌 **نکات مهم**  
- برخی پازل‌ها غیرقابل‌حل هستند و الگوریتم این موارد را شناسایی می‌کند.  
- خروجی شامل تعداد حرکات و حالات بررسی‌شده برای هر الگوریتم است.  

---

### 🤝 **مشارکت**  
هرگونه پیشنهاد یا بهبود را با یک Pull Request برای ما ارسال کنید!  

---

### 🛠️ **ابزارهای استفاده‌شده**  
- زبان برنامه‌نویسی: **C++**  
- کامپایلر: GCC  
- سیستم‌عامل: **Linux/Windows**  

---

### 💡 **ایده‌های آینده**  
- افزودن GUI برای نمایش مراحل حل پازل.  
- پشتیبانی از پازل‌های بزرگ‌تر مانند 15-puzzle.  
- بهبود عملکرد الگوریتم‌های ترکیبی.  

---

### 📬 **تماس با من**  
- [GitHub Profile](https://github.com/Shayanpouryazdan)  
- [X](https://x.com/SHAYANDVLPR)  

---

**⭐ اگر این پروژه برایتان مفید بود، لطفاً ریپوزیتوری را Star کنید!**
