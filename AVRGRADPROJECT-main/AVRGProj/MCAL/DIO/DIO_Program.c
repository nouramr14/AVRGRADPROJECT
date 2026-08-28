/*
 * DIO_Program.c
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */
#include "DIO_Interface.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                          IO Pins                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function set the direction of the Pin  (INPUT || OUTPUT)
 * Parameters :
  	  =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>Copy_u8Direction --> Pin Direction [ DIO_PIN_OUTPUT , DIO_PIN_INPUT ]
 * return : its status
 */
void DIO_enumSetPinDirection    (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Direction )
{

	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((Copy_u8PORT <= DIO_PORTD) && (Copy_u8PIN <= DIO_PIN7))
	{
		if ( Copy_u8Direction == DIO_PIN_OUTPUT )
		{
			/* Check on the Required PORT Number */
			switch (Copy_u8PORT)
			{
			case DIO_PORTA: SET_BIT(DDRA_Register,Copy_u8PIN); break;
			case DIO_PORTB: SET_BIT(DDRB_Register,Copy_u8PIN); break;
			case DIO_PORTC: SET_BIT(DDRC_Register,Copy_u8PIN); break;
			case DIO_PORTD: SET_BIT(DDRD_Register,Copy_u8PIN); break;
			}
		}

		else if ( Copy_u8Direction == DIO_PIN_INPUT )
		{
			/* Check on the Required PORT Number */
			switch (Copy_u8PORT)
			{
			case DIO_PORTA: CLR_BIT(DDRA_Register,Copy_u8PIN); break;
			case DIO_PORTB: CLR_BIT(DDRB_Register,Copy_u8PIN); break;
			case DIO_PORTC: CLR_BIT(DDRC_Register,Copy_u8PIN); break;
			case DIO_PORTD: CLR_BIT(DDRD_Register,Copy_u8PIN); break;
			}
		}

		else
		{
			//Nothing
		}
	}

	else
	{
		//Nothing
	}

}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function set the Value of the Pin  (HIGH || LOW)
 * Parameters :
  	  =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  =>Copy_u8Value --> Pin Direction [ DIO_PIN_HIGH , DIO_PIN_LOW ]
 * return : its status
 */
void DIO_enumSetPinValue      (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Value )
{

	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((Copy_u8PORT <= DIO_PORTD) && (Copy_u8PIN <= DIO_PIN7))
	{
		if (Copy_u8Value == DIO_PIN_HIGH)
		{
			/* Check on the Required PORT Number */
			switch (Copy_u8PORT)
			{
			case DIO_PORTA: SET_BIT(PORTA_Register,Copy_u8PIN); break;
			case DIO_PORTB: SET_BIT(PORTB_Register,Copy_u8PIN); break;
			case DIO_PORTC: SET_BIT(PORTC_Register,Copy_u8PIN); break;
			case DIO_PORTD: SET_BIT(PORTD_Register,Copy_u8PIN); break;
			}

		}

		else if (Copy_u8Value == DIO_PIN_LOW)
		{
			/* Check on the Required PORT Number */
			switch (Copy_u8PORT)
			{
			case DIO_PORTA: CLR_BIT(PORTA_Register,Copy_u8PIN); break;
			case DIO_PORTB: CLR_BIT(PORTB_Register,Copy_u8PIN); break;
			case DIO_PORTC: CLR_BIT(PORTC_Register,Copy_u8PIN); break;
			case DIO_PORTD: CLR_BIT(PORTD_Register,Copy_u8PIN); break;
			}
		}

		else
		{
			//Nothing
		}
	}

	else
	{
		//Nothing
	}


}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Get the Value of the Pin
 * Parameters :
 	  =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
  	  => *Copy_PtrData  --> pointer to recieve the pin value
 * return : its status and recieve Pin Value in pointer
 */

void DIO_enumGetPinValue          (u8 Copy_u8PORT, u8 Copy_u8PIN, u8 * Copy_PtrData   )
{

	if ((Copy_u8PORT <= DIO_PORTD) && (Copy_u8PIN <= DIO_PIN7))
	{
		/* Check on the Required PORT Number */
		switch (Copy_u8PORT)
		{
		case DIO_PORTA: * Copy_PtrData = GET_BIT(PINA_Register,Copy_u8PIN); break;
		case DIO_PORTB: * Copy_PtrData = GET_BIT(PINB_Register,Copy_u8PIN); break;
		case DIO_PORTC: * Copy_PtrData = GET_BIT(PINC_Register,Copy_u8PIN); break;
		case DIO_PORTD: * Copy_PtrData = GET_BIT(PIND_Register,Copy_u8PIN); break;
		}
	}

	else
	{
		/* in case of error in the Pin ID or PORT ID */
		//Nothing
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Toggle the Value of the Pin
 * Parameters :
  	  =>Copy_u8PORT --> Port Name [ DIO_PORTA ,	DIO_PORTB , DIO_PORTC , DIO_PORTD ]
  	  =>Copy_u8PIN  --> Pin Number [ DIO_PIN0 , DIO_PIN1 , DIO_PIN2 , DIO_PIN3 , DIO_PIN4 , DIO_PIN5 , DIO_PIN6 , DIO_PIN7 ]
 * return : its status
 */
void DIO_enumTogglePinValue  ( u8 Copy_u8PORT, u8 Copy_u8PIN )
{

	if (Copy_u8PIN <= DIO_PIN7)
	{
		switch (Copy_u8PORT)
		{
		case DIO_PORTA : TOG_BIT(PORTA_Register,Copy_u8PIN);
		break ;
		case DIO_PORTB : TOG_BIT(PORTB_Register,Copy_u8PIN);
		break ;
		case DIO_PORTC : TOG_BIT(PORTC_Register,Copy_u8PIN);
		break ;
		case DIO_PORTD : TOG_BIT(PORTD_Register,Copy_u8PIN);
		break ;
		}

	}
	else
	{
		/* in case of error in the Pin ID or PORT ID */
		//Nothing
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                          IO PORTS                     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
 * Breif : This Function Set the direction of the port (INPUT / OUTPUT)
 * Parameters :
 	  =>Copy_u8PORT --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 	  =>Copy_u8Direction  --> Port direction [ DIO_PORT_OUTPUT , DIO_PORT_INPUT ]
 * return :  its status
 */
void DIO_enumSetPortDirection   (u8 Copy_u8PORT , u8 Copy_u8Direction )
{


	if ( (Copy_u8PORT <= DIO_PORTD) )
	{
		/* Check on the Required PORT Number */
		switch (Copy_u8PORT)
		{
		case     DIO_PORTA: DDRA_Register = Copy_u8Direction; break;
		case     DIO_PORTB: DDRB_Register = Copy_u8Direction; break;
		case     DIO_PORTC: DDRC_Register = Copy_u8Direction; break;
		case     DIO_PORTD: DDRD_Register = Copy_u8Direction; break;
		default: break;
		}
	}
	else
	{
		//Nothing
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Set value on Port
 * Parameters :
  	  =>Copy_u8PORT --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 	  =>Copy_u8Value  --> The Value  [DIO_PORT_HIGH , DIO_PORT_LOW , Another Value]
 * return : its status
 */
void DIO_enumSetPortValue       (u8 Copy_u8PORT , u8 Copy_u8Value )
{


	if ( (Copy_u8PORT <= DIO_PORTD) && ( (Copy_u8Value<=255) || (Copy_u8Value==DIO_PORT_LOW) || (Copy_u8Value==DIO_PORT_HIGH) ) )
	{
		/* Check on the Required PORT Number */
		switch (Copy_u8PORT)
		{
		case     DIO_PORTA: PORTA_Register = Copy_u8Value; break;
		case     DIO_PORTB: PORTB_Register = Copy_u8Value; break;
		case     DIO_PORTC: PORTC_Register = Copy_u8Value; break;
		case     DIO_PORTD: PORTD_Register = Copy_u8Value; break;
		default: break;
		}
	}
	else
	{
		//Nothing
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function Toggle value on Port
 * Parameters :
 	  =>Copy_u8PORT --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 * return : its status
 */
void DIO_enumTogglePortValue      (u8 Copy_u8PORT                       )
{


	if (Copy_u8PORT <= DIO_PORTD)
	{
		switch (Copy_u8PORT)
		{
		case DIO_PORTA : PORTA_Register = ~PORTA_Register ;
		break ;
		case DIO_PORTB : PORTB_Register = ~PORTB_Register ;
		break ;
		case DIO_PORTC : PORTC_Register = ~PORTC_Register ;
		break ;
		case DIO_PORTD : PORTD_Register = ~PORTD_Register ;
		break ;
		}
	}
	else
	{
		//Nothing
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Breif : This Function GET value on Port
 * Parameters :
 	  =>Copy_u8PORT --> Port Name [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]
 	  => *Copy_PtrData  --> pointer to recieve the port value
 * return : its status and recieve Port Value in pointer
 */
void   DIO_enumGetPortValue         ( u8 Copy_u8PORT  , u8 * Copy_PtrData )
{


	if ( (Copy_u8PORT <= DIO_PORTD))
	{
		switch (Copy_u8PORT)
		{
		case DIO_PORTA :
			*Copy_PtrData = PINA_Register  ;
			break ;
		case DIO_PORTB :
			*Copy_PtrData = PINB_Register  ;
			break ;
		case DIO_PORTC :
			*Copy_PtrData = PINC_Register  ;
			break ;
		case DIO_PORTD :
			*Copy_PtrData = PIND_Register  ;
			break ;
		default : //Nothing
		break;
		}
	}
	else
	{
		//Nothing
	}
}

