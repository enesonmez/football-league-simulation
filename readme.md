<h1>Futbol Lig Simülasyonu (Football League Simulation)</h1>
<p>Bu projede Türkiye Sanal Süper Lig takımlarının ya da bizim oluşturacağımız bir ligin lig fikstürünün hesaplamasını yapan bir program istenmektedir. (This project in Turkey Virtual Super League teams or the league we created that we will create a program that makes the calculation of a league fixture.)</p>
<h2>Projenin Özellikleri (Features of the Project) </h2>
<ol>
  <li>Ligte 10 takım bulunmaktadır. Bu sayı gerekirse değişitirilebilir. (There are 10 teams in the league. This number can be changed if necessary.)</li>
  <li>Galibiyet için 2 puan, beraberlik için 1 puan ve mağlubiyet için -1 puan kazanılır. Gerekirse bu değerler program üzerinden ya da       ayarlar.txt dosyasından değiştirilebilir. (2 points for win, 1 point for draw and -1 point for defeat. If necessary, these values can be changed through the program or from the ayarlar.txt file.)</li>
  <li>Her takımın tek bir karakterden oluşan takma isim ve en fazla 12 karakterden oluşan takım uzun ismi bulunmaktadır. Takımların takma isimleri ‘A’, ‘B’, ‘C’, ‘D’, ‘E’, ‘F’, ‘G’, ‘H’, ‘I’, ‘J’ şeklinde olmalıdır. Takımların uzun isimleri  “takmlar.txt”  dosyasından okunmaktadır. (Each team has a single nickname and long names of the teams maximum of 12 characters long. The nicknames of the teams should be like  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'. Long names of the teams are read from the file "takmlar.txt".)</li>
   <li>Program oynanan maçları klavyeden veya dosyadan (maclar1.txt) giriş olarak alıp puan durumu tablosunu güncellemek amacıyla kullanır. (The program takes the matches played as input from the keyboard or file (maclar1.txt) and uses them to update the standings table.)</li>
   <li>Klavyeden maç girişi yapıldığında “A 3 C 2” şeklinde olmalıdır. Bunun anlamı A takımı ile C takımı maç yapmış, ev sahibi takım A     takımı 3 gol atmış ve misafir takım C ise 2 gol atmıştır. (When a match is entered from the keyboard, it should be "A 3 C 2". This means that team A and team C have played matches, home team team A has scored 3 goals and guest team C has scored 2 goals.)</li>
   <li>Dosyadan giriş yapıldığında ise her bir satır klavyeden yapılan giriş formatında olacaktır. Yani dosyada birden çok maç sonucu       olabilir. (When entering from the file, each line will be in the input format made from the keyboard. So there can be more than one match result in the file.)</li>
   <li>Oynanan maç bir kez daha giriş olarak verildiğinde ekrana uyarı vermektedir ve bu maç paun durumu tablosuna işlenmemektedir. A ve  C takımı A takımının evinde sadece bir kez maç oynamalıdır. (When the played match is given once again as an entry, it warns the screen and this match is not recorded in the table of the score. Team A and C must play only once in team A's home.)</li>
   <li>Puan durumu tablosu ekrana veya dosyaya puan sırasına göre, takımların alfabetik sırasına göre ya da takma isim sırasına göre ekrana yazılabilmektedir. İstendiğinde takım isimleri büyük harf olarak ekrana yazılabilmektedir. (The standings table can be written to the screen or file in order of points, in alphabetical order of the teams, or in order of aliases. When requested, team names can be written on the screen or file in capital letters.)</li>
   <li>Ligdeki takım sayısı, galibiyette, mağlubiyette ve beraberlikte alınacak puan sayısı  ayarlar.txt  dosyasından okunmaktadır. (The number of teams in the league, the number of points to be won in a win, a loss and a draw is read from the ayarlar.txt file.)</li>
    <li> Puan durumu tablosunda bulunan özellikler şunlardır:
1. Takma isim 2. Takım Uzun ismi 3. Oynadığı maç sayısı 4. Galibiyet sayısı 5. Beraberlik sayısı 6. Mağlubiyet sayısı 7. Attığı gol sayısı 8. Yediği gol sayısı 9. Averaj 10. Puan <br> (The features available in the standings table are:
1. Nickname 2. Team Long name 3. Number of games played 4. Number of wins 5. Number of draws 6. Number of losses 7. Number of goals scored 8. Number of goals scored 9. Average 10 points)</li>    
</ol>

<h2>Proje için Ön Şartlar (Project for Prerequisites)</h2>
<p>Bu proje için gerekli olan ön şartlar aşağıda sıralanmıştır:<br>The prerequisites required for this project are listed below:
<ol>
<li>gcc derleyici bilgisayara yüklenmeli. (gcc compiler must be installed on the computer.)</li>
<li>Eclipse, DEV C++, CodeBlocks, Visual Studio vb. IDE ya da editör kurulmalı. (Eclipse, DEV C ++, CodeBlocks, Visual Studio etc. IDE or editor must be installed.)</li>
<li>Aşağıdaki tablodaki gibi dosyalar oluşturulup proje ile aynı dizine konmalıdır. (Biz sizin için örnek dosyalar koyduk.) (Files as in the table below should be created and placed in the same directory as the project. (We put sample files for you.))</p></li>
</ol>
  
<table style="width:100%">
  <tr>
    <th>Dosyalar(Files)</th>
    <th>Dosya İçerik(File Content)</th> 
    <th>Açıklama(Explanation)</th>
  </tr>
  <tr>
    <td>ayarlar.txt(settings.txt)</td>
    <td>10<br>2<br>1<br>-1</td>
    <td>Takım Sayısı(Number of team)<br>Galibiyet Puanı(Win Score)<br>Beraberlik Puanı(Draws Score)<br>Mağlubiyet Puanı(Loss Score)</td>
  </tr>
  <tr>
    <td>takimlar.txt(teams.txt)</td>
    <td>galatasaray<br>fenerbahce<br>trabzonspor<br>kasımpasa<br>arsenal<br>barcelona<br>samsunspor<br>erzurumspor<br>orduspor<br>
    malatyaspor<br>ardahanspor</td>
    <td>Programda yukarıdan aşağı sırası ile alfabetik takma isim veriliyor.('A','B','C',vb.)<br>In the program, alphabetical nicknames are given in order from top to bottom ('A', 'B', 'C', etc.)</td>
  </tr>
  <tr>
    <td>maclar1.txt(matches1.txt)</td>
    <td> A 3 B 0<br> C 0 D 0<br> E 1 F 3<br> G 4 H 5<br> B 0 A 2<br> I 1 J 0<br> B 1 C 2<br> D 3 E 2<br>A 1 B 2</td>
    <td>Maç sonuçları (Matche results)</td>
  </tr>
</table>
  
<h2>Projeyi Çalıştırma(Running the Project)</h2>
<h3>Linux</h3>
<pre>
   <code>
      gcc simulation.c -o simulation
      ./simulation
   </code>
</pre>
<h3>Windows</h3>
<p>Linux kodu çalışmaz ise <b>mingv32</b>'yi bilgisayarınıza kurun ve projenin kurulu olduğu klasöre gidin.<br>(If Linux code does not work, install <b>mingv32</b> on your computer and go to the folder where the project is installed.)</p>
<pre>
   <code>
      mingw32-gcc.exe C:/ProjectLocation/simulation.c -o C:/ProjectLocation/simulation.exe
      C:/ProjectLocation/simulation.exe
   </code>
</pre>

<h2>Geliştiren (Developer)</h2>
Enes Sönmez - @enesonmez

<h2>Lisans (License)</h2>
Bu proje MIT Lisansı altında lisanslanmıştır.
This project is licensed under the MIT License - see the LICENSE.md file for details
