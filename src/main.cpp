
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstring>
using namespace std;

struct BatchRecord
{
    int batchId;
    char wasteType[50];
    float initialWeight;
    float finalWeight;
    char startDate[20];
    char expectedDate[20];
    char status[20];
};

class CompostBatch
{
private:
    int batchId;
    string wasteType;
    float initialWeight;
    float finalWeight;
    string startDate;
    string expectedDate;
    string status;

    static int totalBatches;

public:

    // Default constructor
    CompostBatch()
    {
        batchId = 0;
        initialWeight = 0;
        finalWeight = 0;
        status = "Processing";
    }

    // Parameterized constructor
    CompostBatch(int id, string waste, float weight)
    {
        batchId = id;
        wasteType = waste;
        initialWeight = weight;
        finalWeight = 0;
        startDate = "";
        expectedDate = "";
        status = "Processing";
    }

    // Copy constructor
    CompostBatch(const CompostBatch &obj)
    {
        batchId = obj.batchId;
        wasteType = obj.wasteType;
        initialWeight = obj.initialWeight;
        finalWeight = obj.finalWeight;
        startDate = obj.startDate;
        expectedDate = obj.expectedDate;
        status = obj.status;
    }

    // Destructor
    ~CompostBatch()
    {
    }

    BatchRecord toRecord() const
    {
        BatchRecord r;

        r.batchId = batchId;
        strcpy(r.wasteType, wasteType.c_str());
        r.initialWeight = initialWeight;
        r.finalWeight = finalWeight;
        strcpy(r.startDate, startDate.c_str());
        strcpy(r.expectedDate, expectedDate.c_str());
        strcpy(r.status, status.c_str());

        return r;
    }

    void fromRecord(BatchRecord r)
    {
        batchId = r.batchId;
        wasteType = r.wasteType;
        initialWeight = r.initialWeight;
        finalWeight = r.finalWeight;
        startDate = r.startDate;
        expectedDate = r.expectedDate;
        status = r.status;
    }


    
    bool input(CompostBatch batches[], int count)
    {
        cout << "\nEnter Batch ID: ";

        while (!(cin >> batchId) || batchId < 0)
       {
           cout << "Enter a valid Batch ID: ";
           cin.clear();
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
       }

       if (batchId == 0)
       {
           cout << "\nReturning to Main Menu...";
           return false;
       }

        for (int i = 0; i < count; i++)
        {
            if (batches[i].getBatchId() == batchId)
            {
                cout << "\nError! Batch ID already exists.\n";
                return false;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Waste Type: ";
        getline(cin, wasteType);

        while (wasteType.find_first_not_of(" \t") == string::npos || wasteType.length() >= 50)
        {
            if (wasteType.length() >= 50)
                cout << "Waste type must be less than 50 characters. Enter again: ";
            else
                cout << "Waste type cannot be empty. Enter again: ";
        
            getline(cin, wasteType);
        }

        cout << "Enter Initial Weight (kg): ";

        while (!(cin >> initialWeight) || initialWeight <= 0)
        {
            cout << "Enter a valid positive weight: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Start Date: ";
        getline(cin, startDate);

        while (startDate.empty() || startDate.length() >= 20)
        {
            cout << "Enter a valid start date (maximum 19 characters): ";
            getline(cin, startDate);
        }

        cout << "Enter Expected Completion Date: ";
        getline(cin, expectedDate);

        while (expectedDate.empty() || expectedDate.length() >= 20)
        {
            cout << "Enter a valid expected date (maximum 19 characters): ";
            getline(cin, expectedDate);
        }

        this->finalWeight = 0;
        this->status = "Processing";

        return true;
    }


    void display()
    {
        showBatchDetails(*this);
    }

    inline float getYield() const
    {
        if (initialWeight <= 0)
            return 0;

        return (finalWeight / initialWeight) * 100;
    }

    int getBatchId() const
    {
        return this->batchId;
    }



    static void increaseCount()
    {
        totalBatches++;
    }

    static void setTotalBatches(int n)
    {
        totalBatches = n;
    }

    static int getTotalBatches()
    {
        return totalBatches;
    }

    friend void showBatchDetails(const CompostBatch &b);
};

bool saveBatch(CompostBatch &b)
{
    ofstream file("data/batches.dat", ios::app | ios::binary);

    if (!file)
    {
        cout << "\nError opening file!";
        return false;
    }

    BatchRecord r = b.toRecord();

    file.write(reinterpret_cast<char*>(&r), sizeof(r));

    if (!file)
    {
        cout << "\nError saving batch!";
        return false;
    }

    file.close();

    cout << "\nBatch saved successfully!";
    return true;
}

    void readBatches()
{
    ifstream file("data/batches.dat", ios::in | ios::binary);

    if (!file)
    {
        cout << "\nFile could not be opened!";
        return;
    }

    cout << "\nFile opened successfully!";

    BatchRecord r;
    int total = 0;

    while (file.read(reinterpret_cast<char*>(&r), sizeof(r)))
    {
        CompostBatch b;
        b.fromRecord(r);
        b.display();
        total++;
    }

    cout << "\nTotal records read: " << total;

    file.close();
}

void searchBatch(int id)
{
    ifstream file("data/batches.dat", ios::in | ios::binary);

    if (!file)
    {
        cout << "\nUnable to open file!";
        return;
    }

    BatchRecord r;
    bool found = false;

    int index = 0;

while (true)
{
    file.seekg(index * sizeof(BatchRecord), ios::beg);

    if (!file.read(reinterpret_cast<char*>(&r), sizeof(r)))
    {
        break;
    }

    if (r.batchId == id)
    {
        CompostBatch b;
        b.fromRecord(r);

        cout << "\nBatch Found!";
        b.display();

        found = true;
        break;
    }

    index++;
}

    if (!found)
    {
        cout << "\nBatch not found!";
    }

    file.close();
}

void updateBatch(int id)
{
    fstream file("data/batches.dat", ios::in | ios::out | ios::binary);

    if (!file)
    {
        cout << "\nUnable to open file!";
        return;
    }

    BatchRecord r;
    bool found = false;
    int index = 0;

    while (file.read(reinterpret_cast<char*>(&r), sizeof(r)))
    {
        if (r.batchId == id)
        {
            found = true;
            break;
        }

        index++;
    }

    if (!found)
    {
        cout << "\nBatch not found!";
        file.close();
        return;
    }

    cout << "\nCurrent Final Weight: " << r.finalWeight;

    cout << "\nEnter Final Compost Weight: ";

    while (!(cin >> r.finalWeight) || r.finalWeight < 0 || r.finalWeight > r.initialWeight)
    {
        cout << "Enter weight between 0 and " << r.initialWeight << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string newStatus;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "\nEnter New Status (Processing/Completed/On Hold): ";
    getline(cin, newStatus);
    
    while (newStatus != "Processing" &&
           newStatus != "Completed" &&
           newStatus != "On Hold")
    {
        cout << "Invalid status! Enter Processing, Completed or On Hold: ";
        getline(cin, newStatus);
    }
    
    strcpy(r.status, newStatus.c_str());

    file.clear();
    file.seekp(index * sizeof(BatchRecord), ios::beg);

    file.write(reinterpret_cast<char*>(&r), sizeof(r));

    cout << "\nBatch updated successfully!";

    file.close();
}

void loadBatches(CompostBatch batches[], int &count)
{
    ifstream file("data/batches.dat", ios::in | ios::binary);

    if (!file)
    {
        cout << "\nNo previous records found.";
        return;
    }

    BatchRecord r;

    count = 0;

    while (file.read(reinterpret_cast<char*>(&r), sizeof(r)))
    {
        if (count >= 100)
        {
            break;
        }

        batches[count].fromRecord(r);
        count++;
    }

    file.close();

    cout << "\n" << count << " batches loaded successfully!";
}




int CompostBatch::totalBatches = 0;

void showBatchDetails(const CompostBatch &b)
{
    cout << "\n--------------------------------";
    cout << "\nBatch ID: " << b.batchId;
    cout << "\nWaste Type: " << b.wasteType;
    cout << "\nInitial Weight: " << b.initialWeight << " kg";
    cout << "\nFinal Weight: " << b.finalWeight << " kg";
    cout << "\nStart Date: " << b.startDate;
    cout << "\nExpected Completion Date: " << b.expectedDate;
    cout << "\nStatus: " << b.status;
    cout << "\nYield: ";

    if (b.finalWeight > 0)
        cout << (b.finalWeight / b.initialWeight) * 100 << "%";
    else
        cout << "Not recorded yet";

    cout << "\n--------------------------------\n";
}



int main()
{
    CompostBatch batches[100];

    int count = 0;
    int choice;

    loadBatches(batches, count);
    CompostBatch::setTotalBatches(count);


    do
    {
        cout << "\n================================";
        cout << "\n COMPOSTING BATCH AND YIELD TRACKER";
        cout << "\n================================";
        cout << "\n1. Add New Compost Batch";
        cout << "\n2. View All Compost Batches";
        cout << "\n3. Search Compost Batch";
        cout << "\n4. View Total Number of Batches";
        cout << "\n5. Update Compost Batch";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 6)
        {
            cout << "Enter a valid choice (1-6): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice)
        {
            case 1:
            {
                if (count >= 100)
                {
                    cout << "\nBatch storage is full!";
                    break;
                }
            
                CompostBatch *ptr = &batches[count];
            
                if (ptr->input(batches, count))
                {
                    if (saveBatch(*ptr))
                    {
                        count++;
                        CompostBatch::increaseCount();
                    }
                }
            
                break;
            }

            case 2:
            {
                readBatches();
                break;
            }

           case 3:
            {
                int id;
            
                cout << "\nEnter Batch ID to search: ";
            
                while (!(cin >> id) || id <= 0)
                {
                    cout << "Enter a valid Batch ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            
                searchBatch(id);
            
                break;
            }

            case 4:
            {
                cout << "\nTotal Compost Batches: "
                     << CompostBatch::getTotalBatches();
                break;
            }

            case 5:
            {
                int id;
            
                cout << "\nEnter Batch ID to update: ";
            
                while (!(cin >> id) || id <= 0)
                {
                    cout << "Enter a valid Batch ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            
                updateBatch(id);
                break;
            }

            case 6:
            {
                cout << "\nThank you for using the application!";
                break;
            }
        }

    } while (choice != 6);

    return 0;
}
