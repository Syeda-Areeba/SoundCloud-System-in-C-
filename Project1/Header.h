#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstring>
using namespace std;


class MMD;
class AMD;
class AD;
class ADP;

MMD* mmd_head = NULL;
AMD* amd_head = NULL;
AD* ad_head = NULL;
ADP* adp_head = NULL;

class MMD  //doubly linked list
{
public:
	//data members
	int mbid;
	AD* album;
	string song_name;
	string writer;
	float length;

	//connections
	MMD* next;
	MMD* previous;

	MMD()
	{
		mbid = 0;
		length = 0;
		album = NULL;
		next = NULL;
		previous = NULL;
	}
	void display()
	{
		MMD* temp = this;
		//while (temp != NULL)
		{
			cout << "MBID: " << temp->mbid << endl;
			cout << "Song Name: " << temp->song_name << endl;
			cout << "Writer: " << temp->writer << endl;
			cout << "Length: " << temp->length << endl;
			cout << endl;
			//temp = temp->next;
		}
	}
};

MMD* Create_MMD(string path) //should return head of the MMD linkedlist
{
	ifstream file(path);
	string data, line;

	getline(file, line, '\n'); //reading columns' headings

	if (file.is_open())
	{
		while (getline(file, line)) //inserting at tail
		{
			stringstream word(line);   //parses the line to get individual quantities
			MMD* new_node = new MMD();
			getline(word, data, ',');
			new_node->mbid = atoi(data.c_str());
			getline(word, new_node->song_name, ',');
			getline(word, new_node->writer, ',');
			getline(word, data, ',');
			new_node->length = atof(data.c_str());

			if (mmd_head == NULL) //if there is no node
			{
				mmd_head = new_node;
			}
			else
			{
				MMD* temp = mmd_head;
				while (temp != NULL)
				{
					if (new_node->mbid < temp->mbid)//insert before
					{
						new_node->previous = temp->previous;
						new_node->next = temp;
						if (temp->previous != NULL)
						{
							temp->previous->next = new_node;
						}
						else
						{
							mmd_head = new_node;
						}
						temp->previous = new_node;
						break;
					}
					else if (new_node->mbid > temp->mbid && temp->next == NULL) //insert at tail
					{
						temp->next = new_node;
						new_node->previous = temp;
						break;

					}
					temp = temp->next;
				}
			}
		}
	}
	file.close();
	return mmd_head;
}

//--------------------------------------------------------------------------------------------------------------------
class AMD  //doubly circular linked list
{
public:
	//data members
	int aid;
	AD* albums;
	ADP* adp;

	string name;
	string band;
	string gender;
	int date_of_birth;
	int career_start_date;
	string genre;

	//connections
	AMD* next;

	AMD* previous;

	AMD()
	{
		aid = 0;
		next = NULL;
		previous = NULL;
		date_of_birth = 0;
		career_start_date = 0;
		albums = NULL;
		adp = NULL;
	}
	AMD(AMD* obj)  //deep copy constructor
	{
		aid = obj->aid;
		name = obj->name;
		gender = obj->gender;
		genre = obj->genre;
		career_start_date = obj->career_start_date;
		date_of_birth = obj->date_of_birth;
		next = NULL;
		previous = NULL;
		albums = NULL;
		adp = NULL;
	}
	void display()
	{
		AMD* temp = this;
		/*while (temp->next != this)
		{
			cout << "AID: " << temp->aid << endl;
			cout << "Name: " << temp->name << endl;
			cout << "Band: " << temp->band << endl;
			cout << "Gender: " << temp->gender << endl;
			cout << "Date of birth " << temp->data_of_birth << endl;
			cout << "Career start date: " << temp->career_start_date << endl;
			cout << "Genre: " << temp->genre << endl;
			cout << endl;
			temp = temp->next;
		}*/
		cout << "AID: " << temp->aid << endl;
		cout << "Name: " << temp->name << endl;
		cout << "Band: " << temp->band << endl;
		cout << "Gender: " << temp->gender << endl;
		cout << "Date of birth: " << temp->date_of_birth << endl;
		cout << "Career start date: " << temp->career_start_date << endl;
		cout << "Genre: " << temp->genre << endl;
		cout << endl;
	}
};


AMD* Create_AMD(string path) //should return head of the AMD linkedlist
{
	ifstream file(path);
	string data, line;

	getline(file, line, '\n'); //reading columns' headings

	if (file.is_open())
	{
		while (getline(file, line)) //inserting at tail
		{
			stringstream word(line);
			AMD* new_node = new AMD();
			getline(word, data, ',');
			new_node->aid = atoi(data.c_str());
			getline(word, new_node->name, ',');
			getline(word, new_node->band, ',');
			getline(word, new_node->gender, ',');
			getline(word, data, ',');
			new_node->date_of_birth = atoi(data.c_str());
			getline(word, data, ',');
			new_node->career_start_date = atoi(data.c_str());
			getline(word, new_node->genre, ',');

			if (amd_head == NULL)
			{
				amd_head = new_node;
				new_node->next = amd_head;
				new_node->previous = amd_head;
			}
			else
			{
				AMD* temp = amd_head;
				while (temp->next != amd_head)
				{
					temp = temp->next;
				}
				temp->next = new_node;
				new_node->previous = temp;
				new_node->next = amd_head;
				amd_head->previous = new_node;
			}
		}
	}
	file.close();
	return amd_head;
}
//--------------------------------------------------------------------------------------------------------------------
class Tracks  //singly linked list
{
public:
	//data members
	int trackNumber;
	MMD* trackRef;

	//connections
	Tracks* next;

	Tracks()
	{
		trackNumber = 0;
		trackRef = NULL;
		next = NULL;
	}
	void display()
	{
		Tracks* temp = this;
		while (temp != NULL)
		{
			cout << "Track no. " << temp->trackNumber << endl;
			cout << "MMD: " << endl;
			temp->trackRef->display();
			temp = temp->next;
		}
	}
};
//--------------------------------------------------------------------------------------------------------------------
class AD  //singly circular linked list
{
public:
	//data members
	int abid;
	AMD* author;
	Tracks* tracks;
	ADP* adp;

	string publisher;
	string album_name;
	int total_no_of_tracks;
	float total_duration;

	//connections
	AD* next;

	AD()
	{
		abid = 0;
		total_duration = 0;
		total_no_of_tracks = 0;
		author = NULL;
		tracks = NULL;
		next = NULL;
		adp = NULL;
	}
	AD(AD* obj)  //deep copy constructor
	{
		abid = obj->abid;
		total_duration = obj->total_duration;
		total_no_of_tracks = obj->total_no_of_tracks;
		tracks = obj->tracks;
		publisher = obj->publisher;
		album_name = obj->album_name;
		author = new AMD(obj->author);
		next = NULL;
		adp = NULL;
	}
	void display()
	{
		AD* temp = this;
		/*while (temp->next!=this)
		{
			cout << "ABID: " << temp->abid << endl;
			cout << "Author: " << endl;
			temp->author->display();
			cout << "Publisher: " << temp->publisher << endl;
			cout << "Album Name: " << temp->album_name << endl;
			cout << "No of tracks: " << temp->total_no_of_tracks << endl;
			cout << "Duration: " << temp->total_duration << endl;
			cout << "Tracks: " << endl;
			temp->tracks->display();
			temp = temp->next;
			cout << "-----------------------------------" << endl;
		}*/
		cout << "ABID: " << temp->abid << endl;
		cout << "Author: " << endl;
		temp->author->display();
		cout << "Publisher: " << temp->publisher << endl;
		cout << "Album Name: " << temp->album_name << endl;
		cout << "No of tracks: " << temp->total_no_of_tracks << endl;
		cout << "Duration: " << temp->total_duration << endl;
		cout << "Tracks: " << endl;
		temp->tracks->display();
		cout << "-----------------------------------" << endl;
	}
};

//--------------------------------------------------------------------------------------------------------------------

MMD* Search_Music(int MBID) //should return pointer to track having mbid = MBID
{
	MMD* temp = mmd_head;
	while (temp != NULL)
	{
		if (temp->mbid == MBID)
		{
			break;
		}
		temp = temp->next;
	}
	return temp;  //will return NULL if MBID not found
}

//--------------------------------------------------------------------------------------------------------------------

Tracks* Create_Tracks_List(int no_of_tracks, int starting_mbid, AD* current_album)
{
	//MMD* mmd_head = Create_MMD(MMD_path);
	Tracks* head = NULL;
	int last_mbid = starting_mbid + (no_of_tracks - 1);
	int count = no_of_tracks;
	for (int i = 1; i <= no_of_tracks; i++)
	{
		if (head == NULL)
		{
			head = new Tracks();  //last node in MMD - this function creates list from bottom to top
			head->trackNumber = count--;
			head->trackRef = Search_Music(last_mbid--);
			head->trackRef->album = current_album;   // attaches the track with current album
			// search mbid from MMD, find that node with required mbid and assign it to track ref
		}
		else   //insert at head
		{
			Tracks* new_node = new Tracks();
			new_node->trackNumber = count--;
			new_node->trackRef = Search_Music(last_mbid--);
			new_node->trackRef->album = current_album;
			new_node->next = head;
			head = new_node;
		}
	}
	return head;
}

//--------------------------------------------------------------------------------------------------------------------

AMD* Search_Author(int AID) //should return pointer to author having aid = AID
{
	//AMD* amd_head = Create_AMD(AMD_path);
	AMD* temp = amd_head;
	while (temp->next != amd_head)
	{
		if (temp->aid == AID)
		{
			return temp;
		}
		temp = temp->next;
	}
	if (temp->aid == AID) // checking last node or if there is only 1 node
	{
		return temp;
	}
	return NULL; //means aid not found
}
//--------------------------------------------------------------------------------------------------------------------

AD* assign_albums_to_authors(AD* albums_head, AD* current_album)
{
	AMD* temp = amd_head;
	while (temp->next != amd_head)  //searches and assigns
	{
		if (temp->aid == current_album->author->aid)  //if the aid is found in AMD matches current albums' aid
		{
			if (albums_head == NULL)
			{
				albums_head = new AD(current_album); //if we do not create a shallow copy then all of the classes get disturbed
				break;
			}
			else //insert at tail
			{
				AD* t = albums_head;
				while (t->next != NULL)
				{
					t = t->next;
				}
				t->next = new AD(current_album);
				break;
			}
		}
		temp = temp->next;
	}
	return albums_head;
}

AD* Create_AD(string path) //should return head of the AD linkedlist
{
	ifstream file(path);
	string data, line;

	getline(file, line, '\n'); //reading columns' headings

	if (file.is_open())
	{
		int temp_abid = -1;
		while (getline(file, line)) //inserting at tail
		{
			stringstream word(line);
			AD* new_node = new AD();

			getline(word, data, ',');
			new_node->abid = atoi(data.c_str());
			if (temp_abid != new_node->abid)  //check if previous abid matches the current abid, if so then take it's data
			{
				temp_abid = new_node->abid; // now set current abid as prev abid

				getline(word, new_node->album_name, ',');

				getline(word, data, ',');
				new_node->author = Search_Author(atoi(data.c_str()));
				
				getline(word, new_node->publisher, ',');

				getline(word, data, ',');
				new_node->total_no_of_tracks = atoi(data.c_str());

				getline(word, data, ',');
				new_node->total_duration = atof(data.c_str());

				getline(word, data, ','); //track num

				getline(word, data, ','); //MBID

				AD* current_album = new_node;
				// below function creates a complete track list for each album
				new_node->tracks = Create_Tracks_List(new_node->total_no_of_tracks, atoi(data.c_str()), current_album);

				new_node->author->albums = assign_albums_to_authors(new_node->author->albums, new_node);

				if (ad_head == NULL)   //creating singly circular linked list of AD
				{
					ad_head = new_node;
					new_node->next = ad_head;
				}
				else
				{
					AD* temp = ad_head;
					while (temp->next != ad_head)
					{
						temp = temp->next;
					}
					temp->next = new_node;
					new_node->next = ad_head;
				}
			}
			else
			{
				//do nothing
			}

		}
	}
	file.close();
	return ad_head;
}

//--------------------------------------------------------------------------------------------------------------------

//Albums (A singly linked list)
class Albums
{
public:
	//data members
	int year;
	int abid;
	AD* albumRef;

	//connections
	Albums* next;

	Albums()
	{
		year = 0;
		abid = 0;
		albumRef = NULL;
		next = NULL;
	}
	void display()
	{
		cout << "Year: " << year << endl;
		cout << "Album Reference: " << endl;
		albumRef->display();
	}
};

//--------------------------------------------------------------------------------------------------------------------

//Author Discography Playlist (A circular linked list)
class ADP // it is only displaying first record -check it
{
public:
	//data members
	int did;
	AMD* author;
	Albums* albums;

	//connections
	ADP* next;

	ADP()
	{
		did = 0;
		author = NULL;
		albums = NULL;
		next = NULL;
	}
	void display()
	{
		ADP* temp = this;
		while (temp->next != this)
		{
			cout << "DID: " << did << endl;
			cout << "Author: " << endl;
			author->display();
			cout << "ALbums: " << endl;
			albums->display();
			cout << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl;
			temp = temp->next;
		}
		cout << "DID: " << did << endl;
		cout << "Author: " << endl;
		author->display();
		cout << "ALbums: " << endl;
		albums->display();
		cout << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/" << endl;
	}
};

//--------------------------------------------------------------------------------------------------------------------

AD* Search_Album(int ABID) //should return pointer to album having abid = ABID
{
	AD* temp = ad_head;
	while (temp->next != ad_head)
	{
		if (temp->abid == ABID)
		{
			return temp;
		}
		temp = temp->next;
	}
	if (temp->abid == ABID)
	{
		return temp;
	}
	return NULL;
}

//--------------------------------------------------------------------------------------------------------------------

void assign_discography_to_albums(int abids[],int size,ADP* current_discography)
{
	AD* temp = ad_head;
	for (int count = 0; count < size; count++)
	{
		while (temp->next != ad_head)  //searches and assigns
		{
			if (temp->abid == abids[count])
			{
				temp->adp = current_discography;
				break;
			}
			temp = temp->next;
		}
	}
}

void assign_discography_to_albums(ADP* current_discography)
{
	AMD* temp = amd_head;
	while (temp->next != amd_head)  //searches and assigns
	{
		if (temp->aid == current_discography->author->aid)
		{
			temp->adp = current_discography;
			break;
		}
		temp = temp->next;
	}
}

Albums* insert_at_tail(int abid[], int Year[], int size)
{
	Albums* head = NULL;
	int count = 0;
	while (count < size)
	{
		if (head == NULL)
		{
			head = new Albums();
			head->albumRef = Search_Album(abid[0]);
			head->abid = abid[0];
			head->year = Year[0];
		}
		else
		{
			Albums* temp = head;
			for (int i = 1; i <= size - 1; i++)
			{
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				temp->next = new Albums();
				temp->next->albumRef = Search_Album(abid[i]);
				temp->next->abid = abid[i];
				temp->next->year = Year[i];
			}
		}
		count++;
	}
	return head;
}

ADP* Create_ADP(string path) //should return head of the AD linkedlist
{
	ifstream file(path);
	string data, line;

	getline(file, line, '\n'); //reading columns' headings

	if (file.is_open())
	{
		int temp_did = -1;
		int curr_did = 0;
		int index = 0;
		int temp_abids[3] = { 0 };
		int temp_year[3] = { 0 };
		ADP* new_node = NULL;
		
		while (getline(file, line)) //inserting at tail
		{
			stringstream word(line);
			
			getline(word, data, ',');  //did
			curr_did = atoi(data.c_str());

			if (temp_did != curr_did)  //check if previous abid matches the current abid, if so then take it's data
			{
				if (curr_did >= 2) //2nd time
				{
					new_node->albums = insert_at_tail(temp_abids, temp_year, index);
					if (adp_head == NULL)
					{
						adp_head = new_node;
						new_node->next = adp_head;
					}
					else
					{
						ADP* temp = adp_head;
						while (temp->next != adp_head)
						{
							temp = temp->next;
						}
						temp->next = new_node;
						new_node->next = adp_head;
					}
					assign_discography_to_albums(temp_abids,index,new_node);
					assign_discography_to_albums(new_node);
					index = 0;
				}
				new_node = new ADP();
				new_node->did = curr_did;
				temp_did = new_node->did; // now set current abid as prev abid

				getline(word, data, ','); //aid
				new_node->author = Search_Author(atoi(data.c_str()));
			}
			else  //will only execute when a different did comes
			{
				getline(word, data, ','); //aid
				new_node->author = Search_Author(atoi(data.c_str()));
			}
			getline(word, data, ',');
			temp_abids[index] = atoi(data.c_str());

			getline(word, data, ',');
			temp_year[index] = atoi(data.c_str());

			index++;
		}
		
		if (adp_head == NULL)
		{
			adp_head = new_node;
			new_node->next = adp_head;
		}
		else
		{
			ADP* temp = adp_head;
			while (temp->next != adp_head)
			{
				temp = temp->next;
			}
			temp->next = new_node;
			new_node->next = adp_head;
		}
	}
	file.close();
	return adp_head;
}

//--------------------------------------------------------------------------------------------------------------------

ADP* Search_Discography(int DID)
{
	ADP* temp = adp_head;
	while (temp->next != adp_head)
	{
		if (temp->did == DID)
		{
			return temp;
		}
		temp = temp->next;
	}
	if (temp->did == DID)
	{
		return temp;
	}
	return NULL;
}


Tracks* Search_Music_By_Album(int ABID) //should return singly linklist of "Tracks" in given album
{
	AD* temp = ad_head;
	while (temp->next != ad_head)
	{
		if (temp->abid == ABID)
		{
			return temp->tracks;
		}
		temp = temp->next;
	}
	if (temp->abid == ABID)
	{
		return temp->tracks;
	}
	return NULL;
}


Albums* Search_Music_By_Author(int DID) 
{
	ADP* temp = adp_head;
	while (temp->next != adp_head) 
	{
		if (temp->did == DID) 
		{
			return temp->albums;
		}
		temp = temp->next;
	}
	if (temp->did == DID) 
	{
		return temp->albums;
	}
	return NULL;
}