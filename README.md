                                                                          MPI ve OpenMP Arasındaki Temel Farklar

MPI (Message Passing Interface)
MPI, özellikle dağıtık bellek mimarilerinde kullanılan bir paralel programlama modelidir. Her işlem kendi belleğine sahiptir ve işlemler arasında veri aktarımı mesajlaşma yoluyla sağlanır.

OpenMP (Open Multi-Processing)
OpenMP ise paylaşımlı bellek sistemlerinde çok çekirdekli işlemciler için kullanılır. Tüm iş parçacıkları aynı adres alanını paylaşır ve paralel işlemleme #pragma direktifleriyle gerçekleştirilir.

🟦 OpenMP Özellikleri (Paylaşımlı Bellek Tabanlı)
- Tek makine üzerindeki çok çekirdekli işlemciler için uygundur.

- Paylaşımlı bellek kullanır, tüm thread'ler aynı belleğe erişir.

- İş parçacığı (thread) tabanlı paralelleştirme sağlar.

- #pragma direktifleriyle kullanımı kolaydır.

- Kod yazımı ve hata ayıklama işlemleri görece basittir.

- Thread'ler arasında veri paylaşımı hızlıdır (düşük iletişim gecikmesi).

- Bellek sınırlıdır (makinenin RAM kapasitesi kadar).

- Daha az ölçeklenebilir, sadece tek bilgisayarda çalışır.

- Küçük ve orta ölçekli hesaplamalar için uygundur.

- Paralellik CPU seviyesindedir (çekirdekler arası).

🟧 MPI Özellikleri (Dağıtık Bellek Tabanlı)
- Çoklu makineler (cluster) üzerinde çalışmak için uygundur.

- Her işlem (process) kendi belleğine sahiptir.

- Mesaj tabanlı iletişim (message passing) kullanılır.

- Kodlama daha karmaşıktır; veri paylaşımı için açıkça mesaj gönderilmelidir.

- Süreç (process) tabanlı paralelleştirme sağlar.

- Yüksek ölçeklenebilirlik sunar; binlerce node ile çalışabilir.

- İletişim maliyeti yüksektir (veri transferi gerektiğinden).

- Büyük veri setleriyle çalışmak için idealdir.

- Dağıtık sistemlerde yüksek performanslı hesaplamalar için kullanılır.

- Paralellik ağ (network) üzerinden sağlanır.

YOUTUBE VİDEO LİNKİ [https://youtu.be/N_vPrEZjyNc]
