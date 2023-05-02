#include <stdio.h>
#include <string.h>
#include <qrencode.h>

int main() {
    char data[256];
    char filename[256];

    // Get user input for data and filename
    printf("Enter data to encode: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';  // Remove trailing newline
    printf("Enter filename for QR code: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';  // Remove trailing newline

    // Generate QR code image
    QRcode *qr = QRcode_encodeString(data, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (qr == NULL) {
        fprintf(stderr, "Error: failed to encode QR code\n");
        return 1;
    }

    // Write QR code to file
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Error: failed to open file for writing\n");
        QRcode_free(qr);
        return 1;
    }
    fwrite(qr->data, qr->width, qr->width, fp);
    fclose(fp);

    // Free memory allocated for QR code
    QRcode_free(qr);

    return 0;
}
