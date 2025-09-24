#include<stdio.h>
#include<stdlib.h> // Required for malloc() and free()

// The function returns a pointer to an int, so the return type must be int*
int *process(int *sensor, int n, int maxSensorVal){
    int *processedSensor = (int *)malloc(n * sizeof(int));
    int i = 0;
    while(n > i){
        processedSensor[i] = maxSensorVal - sensor[i];
        i++;
    }
    return processedSensor;
}

float weightAvg(int *sensor, int *weight, int len){
    float sum = 0;
    float weightSum = 0;
    
    int i = 0;
    while(len > i){
        weightSum = weightSum + (sensor[i] * weight[i]);
        sum = (sum + sensor[i]);
        i++;
    }
    
    if (sum == 0) {
        return 0;
    }
    
    printf("\n\nsum = %f\n", sum);
    printf("weightSum = %f\n", weightSum);
    float avg = weightSum / sum;
    return avg;
}
void PidLogic(int pos, int weights){
    float Kp = 0.07, Ki = 0.0008, Kd = 0.6;   // Example values
    float P = 0, I = 0, D = 0,  PIDvalue;
    int base_speed = 1.0f, max_speed = 1.5f;
    float previous_error = 0 , previous_I = 0;
    while(1){
        float error = 0 - pos;
        P = error; 
        I = I + previous_I; 
        D = error - previous_error; 

        PIDvalue = (Kp * P) + (Ki * I) + (Kd * D); 

        previous_I = I; 
        previous_error = error; 
    }
}

int main(){
    // int sensor[] = {0, 1023, 1023, 1023, 1023};
    // int sensor[] = {1023, 0, 1023, 1023, 1023};
    // int sensor[] = {1023, 1023, 0, 1023, 1023};
    // int sensor[] = {1023, 1023, 1023, 0, 1023};
    int sensor[] = {1023, 1023, 1023, 1023, 0};
    int weights[] = {-2, -1, 0, 1, 2};
    int n = sizeof(sensor)/sizeof(sensor[0]);
    int maxThresold = 1023;
    
    printf("Raw Sensor Values:   ");
    for(int i = 0; i < n; i++){
        printf("%5d", sensor[i]);
    }

    int *processedSens = process(sensor,n,maxThresold);
    float position = weightAvg(processedSens, weights, n);
    
    printf("\nCalculated Position = %.1f\n", position);
    
    // Free the dynamically allocated memory to prevent a leak
    free(processedSens);
    
    return 0;
}


// now this repo is private helloe