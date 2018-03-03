// GR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>

using namespace std;

/*
Rules​:
● All items have a SellIn value which denotes the number of days we have to sell the item
● All items have a Quality value which denotes how valuable the item is
● At the end of each day our system lowers both values for every item
● Once the sell by date has passed, Quality degrades twice as fast
● The Quality of an item is never negative
● "Aged Brie" actually increases in Quality the older it gets
● "Normal Item" decreases in Quality by 1
● The Quality of an item is never more than 50
● "Sulfuras", being a legendary item, never has to be sold or decreases in Quality
● "Backstage passes", like aged brie, increases in Quality as its SellIn value
  approaches; Its quality increases by 2 when there are 10 days or less and by 3 when
  there are 5 days or less but quality drops to 0 after the concert
● "Conjured" items degrade in Quality twice as fast as normal items

Test​ ​Input​:
Aged Brie 1 1
Backstage passes -1 2
Backstage passes 9 2
Sulfuras 2 2
Normal Item -1 55
Normal Item 2 2
INVALID ITEM 2 2
Conjured 2 2
Conjured -1 5

Expected​ ​Output​:
Aged Brie 0 2
Backstage passes -2 0
Backstage passes 8 4
Sulfuras 2 2
Normal Item -2 50
Normal Item 1 1
NO SUCH ITEM
Conjured 1 0
Conjured -2 1
*/

int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> vItem;
	vector<int> vValue;
	vector<int> vQuality;

	while (true)
	{
		string sItem;
		int nValue, nQuality;

		while (true)
		{
			cout << "Inventory item (D to advance day, Q to quit): ";
			getline(cin, sItem);

			vector<string> vLine;
			size_t last = 0;
			size_t next = 0;
			while ((next = sItem.find(' ', last)) != string::npos)
			{
				string str = sItem.substr(last, next - last);
				vLine.push_back(str);
				last = next + 1;
			}
			vLine.push_back(sItem.substr(last));

			if (vLine.size() == 1)
			{
				if (sItem.compare("Q") == 0 || sItem.compare("q") == 0 || sItem.compare("D") == 0 || sItem.compare("d") == 0)
					break;
			}
			else if (vLine.size() >= 3)
			{
				sItem = "";
				size_t n = vLine.size() - 2;
				for (size_t i = 0; i < n; ++i)
				{
					sItem += vLine[i];
					if (i < (n - 1))
						sItem += " ";
				}
				nValue = atoi(vLine[vLine.size() - 2].c_str());
				nQuality = atoi(vLine[vLine.size() - 1].c_str());
				break;
			}
			cout << endl << "Invalid entry" << endl << endl;
		}
		
		if (sItem.compare("Q") == 0 || sItem.compare("q") == 0)
			break;
		if (sItem.compare("D") == 0 || sItem.compare("d") == 0)
		{
			for (size_t i = 0; i < vItem.size(); ++i)
			{
				int & iValue = vValue[i];
				int & iQuality = vQuality[i];

				locale loc;
				string strItem = vItem[i];
				transform(strItem.begin(), strItem.end(), strItem.begin(), ::tolower);

				if (strItem.compare("sulfuras") != 0)
					iValue--;

				if (strItem.compare("aged brie") == 0)
				{
					iQuality++;
				}
				else if (strItem.compare("backstage passes") == 0)
				{
					if (iValue > 10)
						iQuality++;
					else if (iValue > 5 && iValue <= 10)
						iQuality += 2;
					else if (iValue > 0 && iValue <= 5)
						iQuality += 3;
					else
						iQuality = 0;
				}
				else if (strItem.compare("conjured") == 0)
				{
					iQuality -= 4;
				}
				else
				{
					if (strItem.compare("normal item") != 0)
					{
						if (strItem.compare("sulfuras") != 0)
						{
							if (iValue < 1)
								iQuality -= 2;
							else
								iQuality--;
						}
					}
					else
						iQuality--;
				}
				
				// Quality can't be negative
				if (iQuality < 0)
					iQuality = 0;
				else if (iQuality > 50)
					iQuality = 50;
			}
		}
		else
		{
			vItem.push_back(sItem);
			vValue.push_back(nValue);
			vQuality.push_back(nQuality);
		}

		cout << endl << "Inventory" << endl << "---------" << endl;
		for (size_t i = 0; i < vItem.size(); ++i)
		{
			locale loc;
			string strItem = vItem[i];
			transform(strItem.begin(), strItem.end(), strItem.begin(), ::tolower);
			if (strItem.compare("invalid item") != 0)
				cout << vItem[i] << " " << vValue[i] << " " << vQuality[i] << endl;
			else
				cout << "NO SUCH ITEM" << endl;
		}
		cout << endl;
	}


	return 0;
}

