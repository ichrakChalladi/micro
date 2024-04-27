#line 1 "C:/Users/Dali/Downloads/nouv/PROJET_MICRO/micro.c"


 sbit LCD_RS at RC2_bit;
 sbit LCD_EN at RC3_bit;

 sbit LCD_D4 at RC4_bit;
 sbit LCD_D5 at RC5_bit;
 sbit LCD_D6 at RC6_bit;
 sbit LCD_D7 at RC7_bit;




 sbit LCD_RS_Direction at TRISC2_bit;
 sbit LCD_EN_Direction at TRISC3_bit;
 sbit LCD_D4_Direction at TRISC4_bit;
 sbit LCD_D5_Direction at TRISC5_bit;
 sbit LCD_D6_Direction at TRISC6_bit;
 sbit LCD_D7_Direction at TRISC7_bit;
 int count=0;
 char txt1[] = "MR Mohamed";
char txt2[] = "Have a good time";
char medicament[] = "Ebixa 10mg 2/J Aricept 10mg 3/J";
 int NB;
int ligne02 = 15;
char medicamenticament01[14];
char medicamenticament02[16];
 int i,j,son=0;
 char Temperature[] = " 00.0 C";
unsigned int Temp;
 unsigned char eeprom_address = 0, write_char, read_char,ii;
 unsigned short take ,take1;
 void servo0 () {
 unsigned int i;
 for (i=0;i<50;i++) {
 PortD.f0=1;
 delay_us(800);
 PortD.f0=0;
 delay_us (19200) ;
 }
 }
 void servo180 () {
 unsigned int i;
 for (i=0;i<50;i++) {
 PortD.f0=1;
 delay_us(2200);
 PortD.f0=0;
 delay_us (17800) ;
 }
 }

 void clignote()
 {
 for(i=0;i<3;i++){
 PORTD.RD3=1;
 delay_ms(1000);
 PORTD.RD3=0;
 delay_ms(1000);
 }}
 void sound(){
 Sound_Init(&PORTD, 5);
 Sound_Play(880, 1000);

 }
 void READ_temp(void)
{
temp = ADC_Read(0);
temp = temp * 5/1023; temp = temp * 100;

}



 void interrupt(){
 if((INTCON.INTF)){


 sound();

 clignote();


 INTCON.INTF=0;
 }
 else if((INTCON.RBIF==1)){
 if(PORTB.RB4==1){
 servo180();
 delay_us(2000);




 } if(PORTB.RB5==1){
 servo0();
 delay_us(2000);


 }
 INTCON.RBIF=0;
 }

if(INTCON.TMR0IF){

 count++;
 if(count==244){

 Sound_Init(&PORTD, 5);
 Sound_Play(880, 1000);

 count=0;

 }

 INTCON.TMR0IF=0;



 }



 }



void main() {
ADCON1 =1;


 TRISB=255;
 TRISD=0;

 INTCON.TMR0IE=1;


 OPTION_REG.T0CS=0;
 OPTION_REG.T0SE=0;
 OPTION_REG.PSA=0;
 OPTION_REG.PS2=1;
 OPTION_REG.PS1=1;
 OPTION_REG.PS0=0;
 INTCON.GIE=1;
 INTCON.INTE=1;
 INTCON.RBIE=1;




PORTD=0;



 ADC_Init();

 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1,1,txt1);
 Lcd_Out(2,1,txt2);

Lcd_Cmd(_LCD_CLEAR);

 for (i = 0; i < 30; i++)
 {
 eeprom_write(i, medicament[i]);
 }



 while(1) {
 PORTD=0;
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1,1,txt1);
 Lcd_Out(2,1,txt2);
 delay_ms(3000);
 son=1;
 Lcd_Cmd(_LCD_CLEAR);


 lcd_out(1, 3, "Temperature:");
 Temp = ADC_Read(0) * 0.489;


 Temperature[1] = (temp / 10) % 10 + 48;
 Temperature[2] = temp % 10 + 48;
 Temperature[5] = 223;

 lcd_out(2, 5, Temperature);
 delay_ms(1000);
 Lcd_Cmd(_LCD_CLEAR);
 if( Temp>39)
 {
 PORTD.RD4=1;
 delay_ms(1000);
 PORTD.RD4=0;
 }else if( Temp<39)
 {
 PORTD.RD2=1;
 delay_ms(1000);
 PORTD.RD2=0;
 }
 for (i = 0; i < 14; i++)
 {
 medicamenticament01[i] = eeprom_read(i);
 }
 for (i = 0; i < 14; i++)
 {
 medicamenticament02[i] = eeprom_read(ligne02);
 ligne02++;
 }
 ligne02 = 15;
 LCD_Cmd(_LCD_CLEAR);
 LCD_Out(1, 1, medicamenticament01);
 LCD_Out(2, 1, medicamenticament02);
 delay_ms(2000);

 }
 }
