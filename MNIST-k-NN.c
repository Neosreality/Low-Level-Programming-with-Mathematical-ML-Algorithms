#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_SIZE 784 // 28x28

// Basit bir k-NN sınıflandırıcı
int knn_predict(unsigned char *image, unsigned char **train_images, unsigned char *train_labels, int num_train) {
    int min_distance = 1000000;
    int predicted_label = -1;

    for (int i = 0; i < num_train; i++) {
        int distance = 0;
        for (int j = 0; j < IMAGE_SIZE; j++) {
            distance += (image[j] - train_images[i][j]) * (image[j] - train_images[i][j]);
        }

        if (distance < min_distance) {
            min_distance = distance;
            predicted_label = train_labels[i];
        }
    }

    return predicted_label;
}

// MNIST görüntülerini okuma fonksiyonu
void read_mnist_images(const char *filename, unsigned char **images, int *num_images) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    int magic_number;
    fread(&magic_number, sizeof(int), 1, file);
    magic_number = __builtin_bswap32(magic_number);
    fread(num_images, sizeof(int), 1, file);

    *images = (unsigned char *)malloc((*num_images) * IMAGE_SIZE * sizeof(unsigned char));
    fread(*images, sizeof(unsigned char), (*num_images) * IMAGE_SIZE, file);
    fclose(file);
}

// MNIST etiketlerini okuma fonksiyonu
void read_mnist_labels(const char *filename, unsigned char **labels, int *num_labels) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    int magic_number;
    fread(&magic_number, sizeof(int), 1, file);
    magic_number = __builtin_bswap32(magic_number);
    fread(num_labels, sizeof(int), 1, file);

    *labels = (unsigned char *)malloc((*num_labels) * sizeof(unsigned char));
    fread(*labels, sizeof(unsigned char), *num_labels, file);
    fclose(file);
}

// Test görüntüsünü dosyadan okuma fonksiyonu
void read_test_image(const char *filename, unsigned char *image) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    // Resmi okuyun (28x28 boyutunda)
    fread(image, sizeof(unsigned char), IMAGE_SIZE, file);
    fclose(file);
}

int main() {
    unsigned char *train_images;
    unsigned char *train_labels;
    int num_train;

    // Eğitim veri setini oku
    read_mnist_images("train-images-idx3-ubyte", &train_images, &num_train);
    read_mnist_labels("train-labels-idx1-ubyte", &train_labels, &num_train);

    // Test etmek için bir görüntü oku
    unsigned char test_image[IMAGE_SIZE];
    read_test_image("test_image.bin", test_image); // test_image.bin, 28x28 boyutunda tek kanallı bir resim dosyasıdır

    // Tahmin yap
    int predicted_label = knn_predict(test_image, &train_images, train_labels, num_train);
    printf("Predicted label: %d\n", predicted_label);

    // Bellek temizliği
    free(train_images);
    free(train_labels);

    return 0;
}
