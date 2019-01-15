/*
________________________________________________________________________________

Treyarch Technical Take-home Test
________________________________________________________________________________


Please read all instructions before starting.

This exam consists of 3 questions.

Complete each of the functions below.  
State the amount of time you took for each problem on the line marked "Time:"
Do not modify function declarations.
You are welcome to use any standard library.
You may use helper functions.
You can assume well-formed input.
If you have any concerns, use your best judgment and add a comment.
Place all your code in this file only.
Do all your own work.
Do not distribute this exam.
Have Fun!

________________________________________________________________________________

*/


#include <assert.h>
#include <iostream>
#include <math.h>
#include <string>

// A struct for representing a 3D Vector with a constructor
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3( float xIn, float yIn, float zIn )
	{
		x = xIn;
		y = yIn;
		z = zIn;
	}
};

// Function Declarations
void TreyArch( int Trey, int Arch, int n );
void PlayerInfo( int stats );
bool CanHearSniper( Vector3 listenerPosition, Vector3 sniperPosition, Vector3 sniperForward, float distance, float cone );




// Main
// Calls functions with sample inputs
// No need to modify this function
int main()
{
	TreyArch( 3, 5, 15 );
	PlayerInfo( 3411782069 );
	CanHearSniper( Vector3( 0.0f, 0.0f, 0.0f ), Vector3( 1000.0f, 0.0f, 0.0f ), Vector3( -1.0f, 0.0f, 0.0f ), 1100.7f, 10 );
	return 0;
}


/////////////////////////////////////
// PLACE ALL CODE BELOW THIS BLOCK //
/////////////////////////////////////


// Problem 1

// TreyArch
// For each number starting from 1 and going up to n, this function prints the following
// "Trey" - If the number is a multiple of Trey OR contains the digit Trey
// "Arch" - If the number is a multiple of Arch OR contains the digit Arch
// "TreyArch" - If the number falls into both categories above
// The number itself if none of the rules above hold for that number
// n - the number up to which this function prints
// Trey - first digit 3 - 9
// Arch - second digit 3 - 9

/*
Sample Input
-----------------------------------------------------------
3 5 15

Sample Output
-----------------------------------------------------------
1 2 Trey 4 Arch Trey 7 8 Trey Arch 11 Trey Trey 14 TreyArch
*/

//Checks if a Source Number contains a specific Target Digit
bool ContainsDigit(int i_SourceNumber, int i_TargetDigit)
{
	int dividend = i_SourceNumber;
	int remainder;

	while (dividend != 0)
	{
		remainder = dividend % 10;
		if (remainder == i_TargetDigit)
		{
			return true;
		}

		dividend = dividend / 10;
	}

	return false;
}

void TreyArch( int Trey, int Arch, int n )
{
	const char* treyString = "Trey";
	const char* archString = "Arch";
	const int maxOutputSize = sizeof(treyString) + sizeof(archString) + 1;
	std::string outputString;
	outputString.reserve(maxOutputSize);        //not much value currently as the max size is smaller than the default capacity

	std::cout << "\n";

	for (int i = 1; i <= n; i++)
	{
		outputString = "";

		//Check for Trey
		if (i % Trey == 0 || ContainsDigit(i, Trey))
		{
			outputString += treyString;
		}

		//Check for Arch
		if (i % Arch == 0 || ContainsDigit(i, Arch))
		{
			outputString += archString;
		}

		//Print output
		if (outputString.empty())
		{
			std::cout << i << "\n";
		}
		else
		{
			std::cout << outputString << "\n";
		}
	}
}

// Time:
    //Design on paper: 6 minutes
    //Implementation: 12 minutes
    //Refactor: 3 minutes
    //Total: 21 minutes




// Problem 2

// PlayerInfo
// Prints the player info stored inside the stats passed in
// From least significant to most significant bits:
// Bits 0 - 7 contain the players kills															Print Number
// Bits 8 - 15 contain the players deaths														Print Number
// Bits 16 - 17 contain the players weapon class												Print "Assault" "SMG" "LMG" or "Sniper"
// Bit 18 is handedness: 1 for right, 0 for left												Print "Right Hand" or "Left Hand"
// Bits 19 - 22 contain the players setting for vertical look sensitivity						Print Number
// Bits 23 - 26 contain the players setting for horizontal look sensitivity						Print Number
// Bits 27 - 30 contain the players setting for auto-aim sensitivity							Print Number
// Bit 31 is if the player is getting an internship at Treyarch: 1 for yes, 0 for no			Print "Yes" or "No"
// stats - the stats blob passed in

/*
Sample Input
-----------------------------------------------------------
3411782069

Sample Output
-----------------------------------------------------------
Kills: 181
Deaths: 169
Class: Sniper
Hand: Left Hand
Vertical Look Sensitivity: 11
Horizontal Look Sensitivity: 6
Auto-Aim Sensitivity: 9
Internship: Yes
*/

enum PlayerWeaponClass
{
	PWD_ASSAULT,
	PWD_SMG,
	PWD_LMG,
	PWD_SNIPER,
	PWD_COUNT,
};

//Extracts bits marked by BitMask and returns value after Right-Shifting by ShiftValue
int inline ExtractNumber(const int & i_BaseNumber, const int & i_BitMask, const int & i_ShiftValue)
{
	int extractedValue = i_BaseNumber & i_BitMask;
	extractedValue = extractedValue >> i_ShiftValue;

	return extractedValue;
}

void PlayerInfo( int stats )
{
	const int killBitPosition = 0;
	const int killMask = 0x00ff << killBitPosition;
	

	const int deathBitPosition = 8;
	const int deathMask = 0x00ff << deathBitPosition;
	

	const int weaponBitPosition = 16;
	const int weaponMask = 0x0003 << weaponBitPosition;
	

	const int handBitPosition = 18;
	const int handMask = 0x0001 << handBitPosition;
	

	const int verticalSensBitPosition = 19;
	const int verticalSensMask = 0x000f << verticalSensBitPosition;
	

	const int horizontalSensBitPosition = 23;
	const int horizontalSensMask = 0x000f << horizontalSensBitPosition;
	

	const int autoAimSensBitPosition = 27;
	const int autoAimSensMask = 0x000f << autoAimSensBitPosition;
	

	std::cout << "\nPlayer Stats:\n";
	
	//Read kills
	int statValue = ExtractNumber(stats, killMask, killBitPosition);
	std::cout << "Kills: " << statValue << "\n";

	//Read Deaths
	statValue = ExtractNumber(stats, deathMask, deathBitPosition);
	std::cout << "Deaths: " << statValue << "\n";

	//Read Weapon Class
	statValue = ExtractNumber(stats, weaponMask, weaponBitPosition);
	switch (statValue)        //cannot currently be greater than 3, so PWD_SNIPER is the last value to check for
	{
	case PWD_ASSAULT:
		std::cout << "Class: Assault \n";
		break;

	case PWD_SMG:
		std::cout << "Class: SMG \n";
		break;

	case PWD_LMG:
		std::cout << "Class: LMG \n";
		break;

	case PWD_SNIPER:
		std::cout << "Class: Sniper \n";
		break;
		
	default:
		std::cout << "Class: Undefined \n";
	}

	//Read Hand
	//statValue = ExtractNumber(stats, handMask, handBitPosition);
	//Can directly compare with handMask or 0 because only 1 bit is needed to be checked
	statValue = stats & handMask;
	if (statValue > 0)
	{
		std::cout << "Hand: Right Hand \n";
	}
	else
	{
		std::cout << "Hand: Left Hand \n";
	}

	//Read Vertical Look Sensitivity
	statValue = ExtractNumber(stats, verticalSensMask, verticalSensBitPosition);
	std::cout << "Vertical Look Sensitivity: " << statValue << "\n";

	//Read Horizontal Look Sensitivity
	statValue = ExtractNumber(stats, horizontalSensMask, horizontalSensBitPosition);
	std::cout << "Horizontal Look Sensitivity: " << statValue << "\n";

	//Read Auto-Aim Sensitivity
	statValue = ExtractNumber(stats, autoAimSensMask, autoAimSensBitPosition);
	std::cout << "Auto - Aim Sensitivity: " << statValue << "\n";


	///////                                 ///////
	// Check and Hope for Internship at Treyarch //
	///////                                ///////

	/*const int internshipBitPosition = 31;
	const int internshipMask = 0x0001 << internshipBitPosition;
	statValue = stats & internshipMask;
	if (statValue == internshipMask)
	{
		std::cout << "Internship: Yes\n";
	}
	else
	{
		std::cout << "Internship: No\n";
	}*/

	//Only works this way because we need to check for just the most significant, the Sign bit, of a signed integer
	if (stats < 0)
	{
		std::cout << "Internship: Yes\n";
	}
	else
	{
		std::cout << "Internship: No\n";
	}
}

// Time:
    //Design on paper: 3 minutes
    //Initial Implementation: 20 minutes
    //Debug and Correction/very minor optimization: 8 minutes
    //Refactor: 6 minutes
    //Total: 37 minutes



// Problem 3

// CanHearSniper
// Task - Complete the function to determine if a player can hear a sniper's gunfire
// Prints true or false for debug purposes

// listenerPosition - The 3d position of the player listening
// sniperPosition - The 3d world position of the sniper
// sniperForward - The normalized vector of the direction that the sniper is firing in
// distance - the max distance that the sniper can be heard from
// cone - the max angle in DEGREES that the sniper's gunfire can be heard in ( 0 - 360 )

/*
Sample Input
-----------------------------------------------------------
Vector3( 0.0f, 0.0f, 0.0f ), Vector3( 1000.0f, 0.0f, 0.0f ), Vector3( -1.0f, 0.0f, 0.0f ), 1100.7f, 10

Sample Output
-----------------------------------------------------------
true
*/

Vector3 inline operator-(const Vector3 & i_lhs, const Vector3 & i_rhs)
{
	return Vector3(i_lhs.x - i_rhs.x, i_lhs.y - i_rhs.y, i_lhs.z - i_rhs.z);
}

float inline dot(const Vector3 & i_lhs, const Vector3 & i_rhs)
{
	return (i_lhs.x * i_rhs.x + i_lhs.y * i_rhs.y + i_lhs.z * i_rhs.z);
}

bool inline AreAboutEqual(const float & i_lhs, const float & i_rhs, const float & epsilon = 0.0000001f)
{
	if (fabs(i_lhs - i_rhs) <= epsilon)
	{
		return true;
	}

	return false;
}

bool CanHearSniper( Vector3 listenerPosition, Vector3 sniperPosition, Vector3 sniperForward, float distance, float cone )
{
	assert(AreAboutEqual(dot(sniperForward, sniperForward), 1.0f));

	std::cout << "\nCan Hear Sniper: ";
	//Check distance between Sniper and Listener
	Vector3 sniperToListenerVec = listenerPosition - sniperPosition;
	float sniperListenerDistanceSquared = dot(sniperToListenerVec, sniperToListenerVec);
	if (sniperListenerDistanceSquared > distance*distance)
	{
		std::cout << "false\n";
		return false;
	}

	//Check if Listener is within half of cone angle
	float angleBetweenSniperFwdListener = acos(dot(sniperToListenerVec, sniperForward)/sqrt(sniperListenerDistanceSquared));
	if (angleBetweenSniperFwdListener <= cone / 2.0f)
	{
		std::cout << "true\n";
		return true;
	}

	std::cout << "false\n";
	return false;
}

// Time:
    //Design on paper: 4 minutes
    //Implementation: 18 minutes
    //Refactor: 3 minutes
    //Total: 25 minutes