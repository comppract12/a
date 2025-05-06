#include <bits/stdc++.h>
using namespace std;

// Job structure with id, deadline, and profit
struct Job
{
    int id;
    int deadline;
    int profit;
};

// Comparison function to sort jobs by descending profit
bool comparison(Job a, Job b)
{
    return a.profit > b.profit;
}

// Function to schedule jobs to maximize total profit
void JobScheduling(Job arr[], int n)
{
    // Step 1: Sort the jobs in decreasing order of profit
    sort(arr, arr + n, comparison);

    // Step 2: Find the maximum deadline to size the schedule
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
    {
        maxDeadline = max(maxDeadline, arr[i].deadline);
    }

    // Step 3: Create a schedule array to track job placement in slots
    // Index 0 is unused because time slots start from 1
    vector<int> schedule(maxDeadline + 1, -1);

    int totalProfit = 0;     // Tracks total profit from scheduled jobs
    int jobsScheduled = 0;   // Counts number of jobs scheduled

    // Step 4: Try to place each job in the latest available slot
    for (int i = 0; i < n; i++)
    {
        // Try to place the job at its deadline, or the closest earlier slot
        for (int j = arr[i].deadline; j > 0; j--)
        {
            if (schedule[j] == -1) // Slot is free
            {
                schedule[j] = i; // Store index of job in arr[]
                totalProfit += arr[i].profit; // Add job's profit
                jobsScheduled++; // Count this job
                break; // Move to next job
            }
        }
    }

    // Step 5: Print scheduled jobs
    cout << "Scheduled Jobs:\n";
    for (int i = 1; i <= maxDeadline; i++)
    {
        if (schedule[i] != -1) // If a job is scheduled in this slot
        {
            Job j = arr[schedule[i]]; // Get the job
            cout << "Job J" << j.id << " (Deadline: " << j.deadline << ", Profit: " << j.profit << ")\n";
        }
    }

    // Step 6: Print total profit
    cout << "\nTotal Profit: " << totalProfit << endl;
}
 
int main()
{
    // Sample job list: {id, deadline, profit}
    Job arr[] = {
        {1, 2, 100},
        {2, 1, 50},
        {3, 2, 10},
        {4, 1, 20},
        {5, 3, 80}
    };

    int n = sizeof(arr) / sizeof(arr[0]); // Number of jobs
    JobScheduling(arr, n); // Call the scheduling function

    return 0;
}
