#include <iostream>
#include <cmath>
#include <random>
std::mt19937 rng(0);
std::uniform_real_distribution<double> randrange(-1, 1);


double monitor_refresh_rate = 60;
bool vsync = true;

double game_update_time() {
    return .00001;
}
double game_render_time() {
    return .02;
}
double game_display_time() {
    return .000001;
}
double busy_time() {
    return .000001;
}

double timing_fuzziness = 1.0 / 60.0 * .005;

double system_time = randrange(rng) * 10000;


double fuzzy(){
    std::uniform_real_distribution<double> dist(-timing_fuzziness, timing_fuzziness);
    return dist(rng);
}

int frame_updates = 0;
double total_updates = 0;
int last_vsync = 0;
int missed_updates = 0;
int double_updates = 0;


void simulate_update(){
    system_time += std::max(0.0, game_update_time() + fuzzy() * .01);
    total_updates++;
    frame_updates++;
}
void simulate_render(){
    system_time += std::max(0.0, game_render_time() + fuzzy() * .01);
}
void simulate_display(){
    if(vsync){
        system_time += std::max(0.0, (ceil(system_time * monitor_refresh_rate) / monitor_refresh_rate) - system_time + fuzzy()); 
    } else {
        system_time += std::max(0.0, game_display_time() + fuzzy());
    }


    int current_vsync = round(system_time * monitor_refresh_rate);
    if(last_vsync != current_vsync){
        for(int i = last_vsync; i<current_vsync-1; i++){
            std::cout << 0;
            missed_updates++;
        }
        std::cout << frame_updates;
        if(frame_updates > 1) double_updates++;
        last_vsync = current_vsync;

        frame_updates = 0;
    }
    
}
void simulate_busy(){
    system_time += std::max(0.0, busy_time() + fuzzy() * .00001);
}


int main() {
    double prev_frame_time = system_time;
    last_vsync = round(system_time * monitor_refresh_rate);
    int first_vsync = last_vsync;

    double accumulator = 0;

    while(total_updates < 10000){
        double current_frame_time = system_time;
        double delta_frame_time = current_frame_time - prev_frame_time;
        accumulator += delta_frame_time;
        prev_frame_time = current_frame_time;

        while(accumulator >= 1.0 / 61.0){
            simulate_update();
            accumulator -= 1.0 / 59.0;

            if(accumulator < 0) accumulator = 0;
        }

        simulate_render();
        simulate_display();
        simulate_busy();
    }

    std::cout << std::endl << std::endl;
    std::cout << "TOTAL UPDATES: " << total_updates << std::endl;
    std::cout << "TOTAL VSYNCS: " << last_vsync-first_vsync << std::endl;
    std::cout << "TOTAL DOUBLE UPDATES: " << double_updates << std::endl;
    std::cout << "TOTAL SKIPPED RENDERS: " << missed_updates << std::endl;

    std::cout << "GAME TIME: " << total_updates*(1.0/60.0) << std::endl;
    std::cout << "SYSTEM TIME: " << (last_vsync-first_vsync)/monitor_refresh_rate << std::endl;
}
