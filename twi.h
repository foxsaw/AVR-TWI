// TWI interface
// ATmega328P
// twi.h
// 23-Dec-2015


#define F_CPU 16000000UL
#define F_TWI 400000UL

#define TWBR_VALUE (((F_CPU)/(F_TWI)-16)/2)

#if ((TWBR_VALUE > 255) || (TWBR_VALUE == 0))
 #error "TWBR value is not correct"
#endif



//---------------------------------------------------------------------------------------
void twi_init(void)
	{
	TWBR = TWBR_VALUE;  //set the twi bitrate
	TWSR = 0x00;        //reset status reg. //prescaler=1
	}


//---------------------------------------------------------------------------------------
void twi_start(void)
	{
	TWCR = 0b10100100;
	while(bit_is_clear(TWCR,TWINT));
	}


//---------------------------------------------------------------------------------------
void twi_write(uint8_t data)
	{
	TWDR = data;
	TWCR = 0b10000100;
	while(bit_is_clear(TWCR,TWINT));
	}


//---------------------------------------------------------------------------------------
uint8_t twi_read(void)
	{
	TWCR = 0b11000100;
	while(bit_is_clear(TWCR,TWINT));
	return TWDR;
	}


//---------------------------------------------------------------------------------------
uint8_t twi_read_end(void)
	{
	TWCR = 0b10000100;
	while(bit_is_clear(TWCR,TWINT));
	return TWDR;
	}


//---------------------------------------------------------------------------------------
void twi_stop(void)
	{
	TWCR = 0b10010100;
	}

