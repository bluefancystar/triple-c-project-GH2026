const int something = 16;

//configures pin modes. here, 'something' is set to provide OUTPUT to the circuit
void setup()
{
  pinMode(something, OUTPUT);
  //begins serial monitor at 115200 baud rate; when reading the monitor, ensure to match the baud rate to this one
  Serial.begin(115200);
}

//main function; repeatedly loops until told otherwise
void loop()
{
  Serial.println("Hello World");
  delay(1000);
}

/* TO DO IF WE SO PLEASE:
  -- some of us should focus on making the website; do research on how to make the website and ESP32(s) talk to each other
  -- the rest of us need to work on designing the ESP32(s) code, physically constructing the system, etc.
  -- if we have time we will focus on aesthetics; functionality should come first
  -- we can use our deepspace credits to help us in debugging/coding for areas we're not knowledgeable in
  -- tutorials will be our best friend
  */
