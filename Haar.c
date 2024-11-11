#include <stdio.h>
#include <stdlib.h>

// Görüntü boyutları
#define WIDTH  24
#define HEIGHT 24

// Haar özelliği hesaplama: Dikdörtgen farkı
int calculate_haar_feature(int* image, int x1, int y1, int x2, int y2) {
    int sum1 = 0;
    
    // İlk bölgenin toplamını hesapla (x1, y1) ile (x2, y2) arasındaki dikdörtgen
    for (int y = y1; y < y2; y++) {
        for (int x = x1; x < x2; x++) {
            sum1 += image[y * WIDTH + x]; // Gri tonlamalı piksel değeri
        }
    }

    return sum1; // Farkı hesaplamak için diğer bölgeyi de aynı şekilde hesaplayabilirsiniz
}

// Basit sınıflandırıcı: Haar özelliği 1000'den büyükse yüz bulundu, küçükse yüz bulunamadı
int simple_classifier(int haar_feature) {
    if (haar_feature > 1000) {
        return 1;  // Yüz bulundu
    } else {
        return 0;  // Yüz bulunamadı
    }
}

int main() {
    // Ö24x24 gri
    int image[WIDTH * HEIGHT];

    // Görüntüyü bir şekilde yükle (bu örnekte sabit bir değer kullanıyoruz)
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        image[i] = i % 255;  // Örnek gri tonları
    }

    // Haar özelliğini hesapla (basit bir dikdörtgen farkı)
    int haar_feature = calculate_haar_feature(image, 0, 0, 12, 12);  // (0,0) ile (12,12) arasındaki fark

    // Basit sınıflandırma
    int result = simple_classifier(haar_feature);

    if (result == 1) {
        printf("Yüz tespit edildi.\n");
    } else {
        printf("Yüz tespit edilmedi.\n");
    }

    return 0;
}
