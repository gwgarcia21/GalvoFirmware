#include "src/GalvoControl.h"
#include <SPI.h>


// SPI Settings
static const int spiClk = 20000000; // 20 MHz
static const uint16_t x_axis = 0x1000;
static const uint16_t y_axis = 0x9000;
SPIClass * hspi = NULL;

// Global
Galvo galvo;

float line_x[1000] = { };
float line_y[1000] = { };

// Functions declarations
void draw_diagonal(void);
void draw_square(void);
void move_to_pos(float new_x, float new_y);
void hspi_transfer(uint16_t out_x, uint16_t out_y);
void hspi_transfer_x(uint16_t out_x);
void hspi_transfer_y(uint16_t out_y);

void setup() {
  Serial.begin(115200);

  //initialise hspi with default pins
  //SCLK = 14, MISO = 12, MOSI = 13, SS = 15
  hspi = new SPIClass(HSPI);
  hspi->begin();
  pinMode(15, OUTPUT); //HSPI SS
}

void loop() {
  //delay(2000);
  //Serial.println("Novo desenho");
  //draw_square();
  //draw_diagonal();
  draw_due_logo();
}

void draw_due_logo() {
  move_to_pos(17.29f, 0.1f);
  move_to_pos(16.74f, 0.64f);
  move_to_pos(16.19f, 1.18f);
  move_to_pos(15.65f, 1.71f);
  move_to_pos(15.11f, 2.24f);
  move_to_pos(14.57f, 2.76f);
  move_to_pos(14.04f, 3.29f);
  move_to_pos(13.49f, 3.82f);
  move_to_pos(12.94f, 4.36f);
  move_to_pos(12.39f, 4.91f);
  move_to_pos(11.82f, 5.47f);
  move_to_pos(11.24f, 6.04f);
  move_to_pos(10.65f, 6.62f);
  move_to_pos(11.81f, 6.62f);
  move_to_pos(12.96f, 6.62f);
  move_to_pos(14.10f, 6.62f);
  move_to_pos(15.22f, 6.63f);
  move_to_pos(16.33f, 6.63f);
  move_to_pos(17.44f, 6.63f);
  move_to_pos(18.53f, 6.63f);
  move_to_pos(19.62f, 6.63f);
  move_to_pos(20.70f, 6.63f);
  move_to_pos(21.78f, 6.62f);
  move_to_pos(22.85f, 6.62f);
  move_to_pos(23.92f, 6.61f);
  move_to_pos(24.74f, 6.62f);
  move_to_pos(25.55f, 6.65f);
  move_to_pos(26.35f, 6.71f);
  move_to_pos(27.15f, 6.80f);
  move_to_pos(27.94f, 6.93f);
  move_to_pos(28.72f, 7.08f);
  move_to_pos(29.49f, 7.26f);
  move_to_pos(30.26f, 7.48f);
  move_to_pos(31.01f, 7.73f);
  move_to_pos(31.77f, 8.01f);
  move_to_pos(32.51f, 8.33f);
  move_to_pos(33.25f, 8.69f);
  move_to_pos(35.06f, 9.74f);
  move_to_pos(36.71f, 10.96f);
  move_to_pos(38.2f, 12.33f);
  move_to_pos(39.52f, 13.83f);
  move_to_pos(40.65f, 15.46f);
  move_to_pos(41.60f, 17.19f);
  move_to_pos(42.36f, 19.01f);
  move_to_pos(42.92f, 20.91f);
  move_to_pos(43.27f, 22.87f);
  move_to_pos(43.41f, 24.88f);
  move_to_pos(43.32f, 26.93f);
  move_to_pos(43.01f, 28.99f);
  move_to_pos(42.5f, 30.87f);
  move_to_pos(41.79f, 32.67f);
  move_to_pos(40.88f, 34.37f);
  move_to_pos(39.8f, 35.97f);
  move_to_pos(38.56f, 37.45f);
  move_to_pos(37.16f, 38.8f);
  move_to_pos(35.63f, 39.99f);
  move_to_pos(33.98f, 41.03f);
  move_to_pos(32.22f, 41.9f);
  move_to_pos(30.37f, 42.58f);
  move_to_pos(28.43f, 43.06f);
  move_to_pos(26.44f, 43.34f);
  move_to_pos(24.81f, 43.45f);
  move_to_pos(23.18f, 43.53f);
  move_to_pos(21.54f, 43.59f);
  move_to_pos(19.91f, 43.62f);
  move_to_pos(18.27f, 43.63f);
  move_to_pos(16.62f, 43.63f);
  move_to_pos(14.97f, 43.61f);
  move_to_pos(13.31f, 43.59f);
  move_to_pos(11.65f, 43.56f);
  move_to_pos(9.97f, 43.54f);
  move_to_pos(8.29f, 43.52f);
  move_to_pos(6.59f, 43.50f);
  move_to_pos(6.59f, 10.74f);
  move_to_pos(6.04f, 11.36f);
  move_to_pos(5.49f, 11.96f);
  move_to_pos(4.95f, 12.56f);
  move_to_pos(4.42f, 13.15f);
  move_to_pos(3.89f, 13.74f);
  move_to_pos(3.36f, 14.32f);
  move_to_pos(2.82f, 14.91f);
  move_to_pos(2.28f, 15.51f);
  move_to_pos(1.73f, 16.12f);
  move_to_pos(1.17f, 16.74f);
  move_to_pos(0.59f, 17.38f);
  move_to_pos(0.00f, 18.03f);
  move_to_pos(0.00f, 49.52f);
  move_to_pos(0.16f, 49.66f);
  move_to_pos(0.32f, 49.78f);
  move_to_pos(0.49f, 49.86f);
  move_to_pos(0.65f, 49.93f);
  move_to_pos(0.82f, 49.97f);
  move_to_pos(0.99f, 49.99f);
  move_to_pos(1.15f, 50.00f);
  move_to_pos(1.32f, 50.00f);
  move_to_pos(1.49f, 49.99f);
  move_to_pos(1.65f, 49.98f);
  move_to_pos(1.81f, 49.97f);
  move_to_pos(1.97f, 49.97f);
  move_to_pos(3.87f, 49.97f);
  move_to_pos(5.77f, 49.98f);
  move_to_pos(7.66f, 49.99f);
  move_to_pos(9.56f, 49.99f);
  move_to_pos(11.46f, 50.00f);
  move_to_pos(13.36f, 50.00f);
  move_to_pos(15.25f, 50.00f);
  move_to_pos(17.15f, 50.00f);
  move_to_pos(19.05f, 50.00f);
  move_to_pos(20.94f, 49.99f);
  move_to_pos(22.84f, 49.98f);
  move_to_pos(24.74f, 49.96f);
  move_to_pos(27.95f, 49.74f);
  move_to_pos(31.04f, 49.15f);
  move_to_pos(33.98f, 48.20f);
  move_to_pos(36.76f, 46.93f);
  move_to_pos(39.34f, 45.36f);
  move_to_pos(41.70f, 43.50f);
  move_to_pos(43.81f, 41.39f);
  move_to_pos(45.66f, 39.03f);
  move_to_pos(47.21f, 36.46f);
  move_to_pos(48.45f, 33.70f);
  move_to_pos(49.34f, 30.77f);
  move_to_pos(49.86f, 27.69f);
  move_to_pos(49.99f, 24.56f);
  move_to_pos(49.74f, 21.50f);
  move_to_pos(49.11f, 18.53f);
  move_to_pos(48.14f, 15.70f);
  move_to_pos(46.83f, 13.01f);
  move_to_pos(45.21f, 10.50f);
  move_to_pos(43.30f, 8.20f);
  move_to_pos(41.11f, 6.13f);
  move_to_pos(38.67f, 4.32f);
  move_to_pos(35.99f, 2.80f);
  move_to_pos(33.10f, 1.59f);
  move_to_pos(30.01f, 0.71f);
  move_to_pos(28.96f, 0.51f);
  move_to_pos(27.91f, 0.34f);
  move_to_pos(26.85f, 0.21f);
  move_to_pos(25.79f, 0.12f);
  move_to_pos(24.73f, 0.06f);
  move_to_pos(23.67f, 0.02f);
  move_to_pos(22.61f, 0.00f);
  move_to_pos(21.54f, 0.00f);
  move_to_pos(20.48f, 0.02f);
  move_to_pos(19.41f, 0.04f);
  move_to_pos(18.35f, 0.07f);
  move_to_pos(17.29f, 0.09f);
  move_to_pos(17.29f, 0.10f);
}

void draw_diagonal() {
  move_to_pos(80.0f,80.0f);
  move_to_pos(0.0f,0.0f);
}

void draw_square() {
  move_to_pos(0.0f,80.0f);
  move_to_pos(80.0f,80.0f);
  move_to_pos(80.0f,0.0f);
  move_to_pos(0.0f,0.0f);
}

void move_to_pos(float new_x, float new_y) {
  //float line_x[1000] = { };
  //float line_y[1000] = { };
  int line_len = 0;
  galvo.line(line_x, line_y, &line_len, new_x, new_y);
  for (int i=0; i < line_len; i++)
  {
    galvo.set_pos(line_x[i], line_y[i]);
    /*Serial.print("X: ");
    Serial.print(line_x[i]);
    Serial.print(" | Y: ");
    Serial.println(line_y[i]);*/
    uint16_t out_x = galvo.output(line_x[i]);
    uint16_t out_y = galvo.output(line_y[i]);
    /*Serial.print("X: ");
    Serial.print(out_x);
    Serial.print(" | Y: ");
    Serial.println(out_y);
    delay(200);*/
    //SPI
    //hspi_transfer(out_x, out_y);
    hspi_transfer_x(out_x);
    hspi_transfer_y(out_y);
    line_x[i] = 0.0f;
    line_y[i] = 0.0f;
  }
  //delay(2000);
}

void hspi_transfer(uint16_t out_x, uint16_t out_y) {
  uint16_t output_data_x = x_axis | out_x;
  uint16_t output_data_y = y_axis | out_y;

  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(15, LOW);
  hspi->transfer16(output_data_x);
  hspi->transfer16(output_data_y);
  digitalWrite(15, HIGH);
  hspi->endTransaction();
}

void hspi_transfer_x(uint16_t out_x) {
  uint16_t output_data_x = x_axis | out_x;

  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(15, LOW);
  hspi->transfer16(output_data_x);
  digitalWrite(15, HIGH);
  hspi->endTransaction();
}

void hspi_transfer_y(uint16_t out_y) {
  uint16_t output_data_y = y_axis | out_y;

  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(15, LOW);
  hspi->transfer16(output_data_y);
  digitalWrite(15, HIGH);
  hspi->endTransaction();
}
