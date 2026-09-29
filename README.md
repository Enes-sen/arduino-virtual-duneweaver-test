# Arduino Virtual DuneWeaver Test 🌀

PlatformIO ve Wokwi kullanılarak geliştirilmiş, **DuneWeaver** (kum masası / polar çizim robotu) mekanizmasının sanal simülasyon projesi. Bu çalışma; Kartezyen $(X, Y)$ koordinatlarını Polar $(\theta, \rho)$ koordinatlarına dönüştüren kinematik hesaplamaları, G-Code ayrıştırmayı ve adım motorlarının denetimini donanımsız bir ortamda test etmek için oluşturulmuştur.

---

## 🎯 Projenin Amacı ve Özellikleri

- **Polar Kinematik Dönüşümü:** Kartezyen düzlemdeki $(X, Y)$ noktalarını, dairesel kum masasının gerektirdiği $\theta$ (açısal dönme) ve $\rho$ (yarıçap ekseni) hareketlerine çevirir.
- **G-Code Ayrıştırma (Parser):** Seri port üzerinden gelen `G0` ve `G1` hareket komutlarını anlık olarak okur ve ilgili koordinatlara doğrusal interpolasyon uygulayarak motor adımlarına böler.
- **Çift Eksenli Step Motor Kontrolü:** `AccelStepper` kütüphanesi ve A4988 sürücüleri ile yumuşak ivmelenme ve hassas konumlandırma sağlar.
- **Sanal Test Ekosistemi:** Donanım bileşenlerine ihtiyaç duymadan VS Code ve Wokwi eklentisi üzerinden kod ve devre davranışını anlık simüle eder.

---

## 🏗️ Sistem Mimarisi ve Çalışma Akışı

Aşağıdaki şema, kullanıcı komutunun Seri Port üzerinden alınıp motor adımlarına dönüştürülmesine kadar geçen yazılım katmanlarını ve modül ilişkilerini göstermektedir:

```mermaid
graph TD
    SO((Serial Operator))

    subgraph Command Input
        AL[Arduino Loop<br>main.cpp]
        GP[G-code Parser<br>GCodeParser.cpp]
    end

    subgraph Motion Planning
        LK[Line Kinematics<br>Kinematics.cpp]
    end

    subgraph Motor Control
        MCT[Motor Controller<br>MotorController.cpp]
    end

    AS[AccelStepper]

    SO -->|sends commands| AL
    AL -->|listens serial| GP
    GP -->|prints status| SO
    GP -->|plans line| LK
    LK -->|sets steps| MCT
    LK -->|runs motion| MCT
    AL -->|runs axes| MCT
    MCT -->|commands steppers| AS
