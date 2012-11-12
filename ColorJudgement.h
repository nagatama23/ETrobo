/****************************************************
 *  ColorJudgement.h                                         
 *  Created on: 2012/05/05 13:52:39                      
 *  Implementation of the Class ColorJudgement       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#if !defined(EA_0311591B_68F8_4d9d_A572_FDE0A82543E8__INCLUDED_)
#define EA_0311591B_68F8_4d9d_A572_FDE0A82543E8__INCLUDED_


#include "Color.h"

#include "LightSensor.h"


// ‘®«‚ğ•Û‚·‚é‚½‚ß‚Ì\‘¢‘Ì‚Ì’è‹`
typedef struct ColorJudgement
{
	unsigned int threshold;
	LightSensor *lightSensor;
} ColorJudgement;

// ŒöŠJ‘€ì
void ColorJudgement_init(ColorJudgement* this);
COLOR ColorJudgement_judgeColor(ColorJudgement* this);

#endif /*!defined(EA_0311591B_68F8_4d9d_A572_FDE0A82543E8__INCLUDED_)*/

