# integrated\_nRF5\_SDK\_15.3.0\_59ac345
nRF5\_SDK\_15.3.0\_59ac345 examples with obvious integrated. The following constraints apply:

1. Currently, only the ARM GCC toolchain has been tested.
2. The Nordic PCA10040 and PCA10056 development kits with SoftDevices S132 and S140, respectively, are currently the only supported targets.
3. Ensure that the nRF Command Line Tool nrfjprog is installed on your computer. It can be found [here](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Command-Line-Tools).


## Step-By-Step Integration Guide
1. Clone this repository with the command ```git clone https://github.com/justaddobvious/integrated_nRF5_SDK_15.3.0_59ac345.git```  
and initialize submodules using the command ```git submodule --init```
2. Create a new Obvious portal on [our website](https://portal.obvious.xyz/create).
3. Once logged in, navigate to the "Tools" tab, select "Command Line Tools", and click "Download". Once the download has finished, install the tool to your machine.
4. Click on the "Products" tab, and create a new product by clicking "Add" in the top-right corner of the page. 
  * For these examples, name your product "Example Product".
  * The feature region size should be 4096.
5. Click on your product, and create a new feature by clicking "Add" in the top-right corner of the product's "Features" tab.
  * For these examples, name your feature "Feature LED 4". If you wish to evaluate the ble\_app\_uart example, name your feature "Feature UART".
  * Using the drop-down list, select "Purchasable" as the option for how the feature is to be delivered.
  * Toggle the "Feature Status" button to the "on" position.
6. Add the feature to your product's catalog.
  * Navigate to the portal's "Sales" tab, and select the "Catalog" option . 
  * Select your product, and then click the "Add" button in the top-right corner of the page.
  * Select "Individual" as the type of catalog item from the first drop-down menu, and select the name of your feature from the second drop-down menu.
  * Give your catalog entry a name, description, SKU, and a price. Enter image and thumbnail URLs if you wish. Then, click the "Add Individual Entry" button at the bottom of the form.
7. Build and download the embedded library.
  * Select the portal's "Products" tab, click on your product, and then select the "Firmware" tab on the left side of the page.
  * Select the "Library" option, and click "Create" in the top-right corner of the page.
  * If you're using the PCA10040 nRF52832 development kit, perform the following:
    * Select SoftDevice S132, and choose version 6.1.1 from the drop-down list.
    * Select NRF52832_XXAA as your chip.
    * Set Ocelot Flash Start to 0x7B000, and Ocelot Reset Safe Ram Start to 0x2000FFF8.
  * If you're using the PCA10056 nRF52840 development kit, perform the following:
    * Select SoftDevice S140, and choose version 6.1.1 from the drop-down list.
    * Select NRF52840_XXAA as your chip.
    * Set Ocelot Flash Start to 0xFB000, and Ocelot Reset Safe Ram Start to 0x2003FFF8.
  * Click "Generate SDK library".
  * Once the build finishes, click "Download" on the card displaying your build's details and extract the .zip file to a location of your choosing.
8. Build and download ocelot DFU. 
  * Select the portal's "Products" tab, click your product, and then select the "Firmware" tab on the left side of the page.
  * Select the "DFU" option, and click "Create" in the top-right corner of the page.
  * If you're using the PCA10040 nRF52832 development kit, perform the following:
    * Select SoftDevice 132, and choose S132 version 6.1.1 from the drop-down list.
    * Select NRF52832_XXAA as your chip.
    * Set Ocelot Flash Start to 0x7B000, and Ocelot Reset Safe Ram Start to 0x2000FFF8.
    * Set DFU Storage Start to 0x4B000, and DFU Storage Size to 0x27000.
    * Set DFU Firmware Flash Start to 0x75000, set DFU Info Start to 0x7E000, and set DFU MBR Info Start to 0x7F000.
  * If you're using the PCA10056 nRF52840 development kit, perform the following:
    * Select SoftDevice 140, and choose S140 version 6.1.1 from the drop-down list.
    * Select NRF52840_XXAA as your chip.
    * Set Ocelot Flash Start to 0xFB000, and Ocelot Reset Safe Ram Start to 0x2003FFF8.
    * Set DFU Storage Start to 0x8B000, and DFU Storage Size to 0x67000.
    * Set DFU Firmware Flash Start to 0xF5000, set DFU Info Start to 0xFE000, and set DFU MBR Info Start to 0xFF000.
  * Give your DFU a name, and then click "Generate DFU library".
  * Once the build finishes, click "Download" on the card displaying your DFU build's details and extract the .zip file to a location of your choosing. 
9. Navigate to the portal's "Tools" tab, select the "Product File Generators" option, and click "Embedded" on the right side of the page to download a file that contains information concerning your products and features called "ocelot\_feature.h".
10. Copy the files "ocelot.h" and "libocelot.ld" from the SDK library folder extracted in step 6 as well as "ocelot\_feature.h" to $(INSTALL\_ROOT)/ocelot/include/
11. Copy the lib folder to $(INSTALL\_ROOT)/ocelot/
12. Flash Ocelot DFU Bootloader
  * Erase the flash on the development kit: ```nrfjprog --eraseall```
  * Program the Ocelot DFU from the extracted Example_Product\_ocelotdfu\_X.X.X directory: ```nrfjprog --program $(OCELOT_DFU_ROOT)/bin/podboot.hex```
13. Navigate to the Makefile of the example you wish to evaluate. For example, if you would like to evaluate the ble\_app\_blinky example on the PCA10040 nRF52832 development kit, navigate to ```$(INSTALL_ROOT)/obvious_examples/ble_peripheral/ble_app_blinky/pca10040/s132/armgcc```
14. Set the GNU\_INSTALL\_ROOT environment variable to /usr/local/gcc-arm-none-eabi-7-2018-q2-update/bin/ and ensure that ARM GCC 7-2018-q2-update is indeed located in the aforementioned location.
15. Build the example by entering the ```make``` command.
16. Program the example onto your development kit by entering ```make flash_softdevice```, and then ```make flash```.
17. Use obviousutil to generate and program the DFU settings for the example you wish to evaluate: 
```
obviousutil settings generate --application path/to/app/hex/file --application-version-string R.M.m
--startaddress dfu_info_start_addr --program
```
  * Choose R.M.m as 1.3.0 for the application version string, as that is what is defined by default.
  * The DFU info start address, as stated in step 8, should either be 0x7E000 (PCA10040 nRF52832 development kit) or 0xFE000 (PCA10056 nRF52840 development kit).
18. Back in the portal, select your product and navigate to the "Keys" page. Then, make note of your 16-byte product key and initialize your device using obviousutil:
```
obviousutil init generate --key your_product_key --start-address ocelot_flash_start --program
```
  * Ocelot flash start, as stated in step 8, should either be 0x7B000 (PCA10040 nRF52832 development kit) or 0xFB000 (PCA10056 nRF52840 development kit).
19. In the Obvious Discover app, select your device from the scan menu. You may wish to filter the list by tapping the three dots on the top-right side of the screen.
20. Once your device has been selected, it will be provisioned automatically, and a feature update will occur. Notice that LED 4 on the development kit is not on. If you are evaluating the ble\_app\_uart example, notice that messages will be printed to the terminal backwards.
21. Navigate to the app's checkout tab, select your feature, and tap "Checkout". To purchase the feature, use the test Visa number 4242424242424242 with expiry 10/30 and CVV 123.
22. Once the purchase is complete, notice that LED 4 on the development board is turned on. If you are evaluating the ble\_app\_uart example, notice that messages are now printed to the terminal properly.
23. Return to the device menu and experiment with toggling the feature that was just purchased by tapping the button at the bottom of the card titled with the feature's name. In this way, the purchased feature can easily be activated and deactivated on the device!
24. Upload new firmware to your portal
  * Update the sample application's version by opening ```$(INSTALL_ROOT)/ocelot/src/m_ocelot.c``` and changing the "major" value in the struct "m\_ocelot\_init\_info" from 3 to 4. 
  * Navigate back to your sample application's armgcc/ directory, and rebuild the application with the ```make``` command.
  * Generate an encrypted firmware package with obviousutil, making sure to choose 1.4.0 as R.M.m:
```
obviousutil pkg generate --key your_product_key --application path/to/hex/file --application-version-string R.M.m output_filename
```
  * Back in your portal, go to the "Products" tab in the top-left corner of the page and then click your product's card.
  * Click "Firmware" on the left side of the page and then select "List".
  * Click the "Add" button in the top-right corner of the page and perform the following in the dialog that pops up:
    * Click the "Choose file" button and select your encrypted firmware package created with obviousutil.
  		* Enter 1.4.0 as the version.
  		* Enter Min Version 0.0.0 and Max Version 999.999.999. This defines which version of firmware can be updated to your new       firmware.
  		* Enter some Release Notes, a Post Update Message, and a Comment if you wish.
  		* Click the "Create firmware" button at the bottom of the dialog.
25. Create a group for your device and add your new firmware
  * In your portal, click the "Products" tab in the top-left corner, then click "Groups" on the left side of the page.
  * Click "Add" in the top-right corner of the page and perform the following in the dialog that pops up:
    * Name your group "Example Group".
  		* Give your example group a description if you wish.
  		* Select a priority level of 0 from the drop-down menu.
  		* Click the "Create group" button on the bottom of the dialog.
  * Click the new "Example Group" card that was just added to your groups list.
  * Click the "Add" button in the top-right corner of the page and perform the following in the dialog that pops up:
      * Select the new firmware you added to your portal in the previous step by selecting its version from the "Select             Firmware" drop-down menu.
  		  * Enter 1.0.0 as your "Android Minimum Version".
  		  * Enter 1.0.0 as your "iOS Minimum Version".
  		  * Add a comment if you wish.
  	   * Click the "Add assignment" button at the bottom of the dialog.
  * Within the "Example Group" page, select the "Devices" tab near the top of the page, NOT the "Devices" tab on the left       side of the page.
  * Click the "Add" button on the right side of the page, enter your device serial number into the "Find a device to add"       field of the dialog that pops up, and click the "Add device" button at the bottom of the dialog.
26. Update your device firmware OTA via the Obvious Discover app
  * In the Obvious Discover app, select your device from the scan menu. You may wish to filter the list by tapping the three     dots on the top-right side of the screen.
  * Once your device has been selected, the provisioning state will be checked, and a feature update will be verified.
  * Next to "Firmware version" information there is a teal refresh button, press it and the current firmware version will be checked.
  * A prompt will appear asking if you'd like to update the firmware, select yes and your new firmware will be uploaded onto     your device!

  
