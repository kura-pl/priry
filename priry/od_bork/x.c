#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
uint8_t rtc_days_numbers[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

uint16_t TIME1B = 3*60 + 1;
uint16_t TIME1E = 23*60 + 59;
uint16_t TIME2B = 0;
uint16_t TIME2E = 1*60 + 59;

uint8_t time_calc_offset(uint8_t hour, uint8_t minutes, uint8_t day, uint8_t month, uint8_t year, uint8_t day_first, uint8_t day_last, uint8_t first_month, uint8_t last_month, uint8_t months_number)
{
	//wynik 0 -> poza zakresem
		//wynik 1 -> w zakresie
			
				uint16_t tmp = hour*60 + minutes;
					
						if(month == first_month && day == day_first && tmp >= TIME1B && tmp <= TIME1E)
							{
									return 1;
										}
											if(day > day_first && day <= rtc_days_numbers[first_month - 1] && month == first_month)
												{
														return 1;
															}
																if((month > first_month && month < last_month && first_month < last_month) || (((month > first_month && month < 13) || (month > 0 && month < last_month)) && first_month > last_month))
																	{
																			return 1;
																				}
																					if(day > 0 && day < day_last && month == last_month)
																						{
																								return 1;
																									}
																										if(month == last_month && day == day_last && tmp >= TIME2B && tmp <= TIME2E)
																											{
																													return 1;
																														}
																															
																																return 0;
																																}
 
int main(void)
{
	int d = time_calc_offset(0, 44,    1, 1, 16,    30, 27, 10, 3, 4);
	printf("%d\n", d);
	return 0;
}

