# MA-FrameworkLatency

## Structure

📁 **analysis**
<br>Includes notebooks analysis measurement data, and all figures (generated plots)
<br>|___📁 pixel_reader_validation: validation data (graphics memory accessing frequency) and analysis notebooks for validation

📁 **data**
<br>Includes measurement data (CSV files)
<br>|___📁 finals_frameworks: measurement data for framework latency (all complexity conditions as well as small and large conditionn)
<br>|___📁 finals_game_engines: measurement data for game engines
<br>|___📁 finals_psycho: measurement data for software used for psychological experiments
<br>|___📁 mouse_latency_data: data including mouse latency measurements
<br>|___📁 vsync_off_60hz: measurement data with disabled VSYNC on 60hz
<br>|___📁 vsync_on_60hz: measurement data with enabled VSYNC on 60hz
<br>|___📁 vsync_on_500hz: measurement data with enabled VSYNC on 500hz

📁 **fraLa_projects**
<br>Includes project files for the FRAmework LAtenca tester

📁 **fraLa_tester**
<br>Includes executables for the FRAmework LAtenca tester
<br>|___📁 data: by default, results of FraLa are placed within this directory. currently including data of one example measurement series

📁 **framework_tester_apps**
<br>Includes executables for all the frameworks

📁 **framework_tester_projects**
<br>Includes project files for all the frameworks

📁 **fullscreen_tester**
<br>Includes test scripts to query the current notification state of our default test applications

📁 **pixel_reader_projects**
<br>Includes project files for our measurement programs (adjusted version for our automated test runs including end-to-end measurements)

📁 **pixel_readers**
<br>Includes executables for our measurement programs (adjusted version for our automated test runs including end-to-end measurements)

📁 **vsync_tester**
<br> Includes scripts for automatically detect VSYNC state

🗎 `fylamd.py`
<br>controlls yalmd, starts framework measurements with simultaneously measuring end-to-end latency, and saves data

🗎 `start_measuremnet.sh`
<br>starts a single measurement series and the `fyalmd`-script for a given pixel reader and a given framework tester

🗎 `start_measurement_series.sh`
<br>starts multiple measurement series with each of the available pixel readers for each of the available framework testers

🗎 `noise.png`
<br>the image displayed in test applications of image condition

<br><br>_Testers and Readers compiled for Windows 11._

---

## Usage of FraLa

<br> To run a measurement series, start your application to test.
Then, you can run your measurement series using FraLa:

1. run `frala_tester.py` and pass required arguments: number of measurements and measurement program
   <br> example: `python frala_tester.py 200 windup`
   <br> optionally, you can pass:
      - an output directory (default: `./data`)
      - a position of the pixel you want to observe (default: 5,5)
      - if the program should terminate as soon as the measurement program could not detect a change in graphics memory (default: False)
   
   <br> example: `python frala_tester.py 200 windup ./my_data 100,100 True`

3. Switch tabs to your test application
4. FraLa will indicate the start of the measurement series by playing a short acoustic signal
5. Wait...
6. As soon as FraLa finished the measurements, you will hear another acoustic signal
7. in the out folder, there is now a CSV file containing the measurement data as well as a visualization of the results (svg)
