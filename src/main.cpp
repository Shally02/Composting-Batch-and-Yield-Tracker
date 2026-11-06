
#include <iostream>
#include <string>
#include <limits>
using namespace std;

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

    CompostBatch()
    {
        batchId = 0;
        initialWeight = 0;
        finalWeight = 0;
        status = "Processing";
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

        while (wasteType.find_first_not_of(" \t") == string::npos)
        {
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

        while (startDate.empty())
        {
            cout << "Enter a valid start date: ";
            getline(cin, startDate);
        }

        cout << "Enter Expected Completion Date: ";
        getline(cin, expectedDate);

        while (expectedDate.empty())
        {
            cout << "Enter a valid expected date: ";
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

    void searchBatch(int id)
{
    if (this->batchId == id)
    {
        display();
    }
}

    static void increaseCount()
    {
        totalBatches++;
    }

    static int getTotalBatches()
    {
        return totalBatches;
    }

    friend void showBatchDetails(const CompostBatch &b);
};

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

    do
    {
        cout << "\n================================";
        cout << "\n COMPOSTING BATCH AND YIELD TRACKER";
        cout << "\n================================";
        cout << "\n1. Add New Compost Batch";
        cout << "\n2. View All Compost Batches";
        cout << "\n3. Search Compost Batch";
        cout << "\n4. View Total Number of Batches";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 5)
        {
            cout << "Enter a valid choice (1-5): ";
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
                    count++;
                    CompostBatch::increaseCount();
                
                    cout << "\nBatch added successfully!";
                }
            
                break;
            }

            case 2:
            {
                if (count == 0)
                {
                    cout << "\nNo compost batches available.";
                }
                else
                {
                    cout << "\n========== ALL COMPOST BATCHES ==========";

                    for (int i = 0; i < count; i++)
                    {
                        CompostBatch *ptr = &batches[i];
                        ptr->display();
                    }
                }

                break;
            }

            case 3:
            {
                int id;
                bool found = false;
            
                cout << "\nEnter Batch ID to search: ";
            
                while (!(cin >> id) || id <= 0)
                {
                    cout << "Enter a valid Batch ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            
                for (int i = 0; i < count; i++)
                {
                    if (batches[i].getBatchId() == id)
                    {
                        cout << "\nBatch Found!";
                        batches[i].display();
                        found = true;
                        break;
                    }
                }
            
                if (!found)
                {
                    cout << "\nBatch not found!";
                }
            
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
                cout << "\nThank you for using the application!";
                break;
            }
        }

    } while (choice != 5);

    return 0;
}
