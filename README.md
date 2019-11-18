# integrated\_nRF5\_SDK\_15.3.0\_59ac345
nRF5\_SDK\_15.3.0\_59ac345 examples with obvious integrated. Currently, only the PCA10040 development kit with SoftDevice S132 and an ARM GCC toolchain are supported. Note that the following guide was developed using a macOS environment. To test the non-Obvious functionality of the examples, please refer to the [Nordic Semiconductor Infocentre](https://infocenter.nordicsemi.com/topic/com.nordic.infocenter.sdk5.v15.3.0/examples_ble_peripheral.html).

## Step-By-Step Integration Guide
1. Clone this repository with the command ```git clone https://github.com/justaddobvious/integrated_nRF5_SDK_15.3.0_59ac345.git```  
and initialize submodules using the command ```git submodule --init```
2. Create a new Obvious portal on [our website](https://portal.obvious.xyz/create).
3. Once logged in, create a new product by clicking "Add" in the top-right corner of the portal's "Products" tab. 
  * For these examples, name your product "Example Product"
  * The feature region size should be 4096.
4. Click on your product, and create a new feature by clicking "Add" in the top-right corner of the product's "Features" tab.
  * For these examples, name your feature "Feature LED 4". If you wish to evaluate the ble\_app\_uart example, name your feature "Feature UART".
  * Using the drop-down list, select "Purchasable" as the option for how the feature is to be delivered.
  * Toggle the "Feature Status" button to the "on" position.
5. Add the feature to your product's catalog.
  * Navigate to the portal's "Sales" tab, and select the "Catalog" option.
  * Select your product, and then click the "Add" button in the top-right corner of the page.
  * Select "Individual" as the type of catalog item from the first drop-down menu, and select the name of your feature from the second drop-down menu.
  * Give your catalog entry a name, description, SKU, and a price. Enter image and thumbnail URLs if you wish. Then, click the "Add Individual Entry" button at the bottom of the form.
6. Build and download the embedded library.
  * Select the portal's "Products" tab, click on your product, and then select the "Firmware" tab on the left side of the page.
  * Select the "Library" option, and click "Create" in the top-right corner of the page.
  * Select SoftDevice S132, and choose version 6.1.1 from the drop-down list.
  * Select NRF52832\_XXAA as your chip.
  * Set Ocelot Flash Start to 0x7B000, and Ocelot Reset Safe Ram Start to 0x2000FFE0
  * Click "Generate SDK library".
  * Once the build finishes, click "Download" on the card displaying your build's details and extract the .zip file to a location of your choosing.
7. Build and download ocelot DFU. 
  * Select the portal's "Products" tab, click your product, and then select the "Firmware" tab on the left side of the page.
  * Select the "DFU" option, and click "Create" in the top-right corner of the page.
  * Select SoftDevice 132, and choose S132 version 6.1.1 from the drop-down list.
  * Select NRF52832_XXAA as your chip.
  * Set Ocelot Flash Start to 0x7B000, and Ocelot Reset Safe Ram Start to 0x2000FFF8.
  * Set DFU Storage Start to 0x4B000, and DFU Storage Size to 0x27000.
  * Set DFU Firmware Flash Start to 0x75000, set DFU Info Start to 0x7E000, and set DFU MBR Info Start to 0x7F000.
  * Give your DFU a name, and then click "Generate DFU library".
  * Once the build finishes, click "Download" on the card displaying your DFU build's details and extract the .zip file to a location of your choosing. 
8. Navigate to the portal's "Tools" tab, select the "Product File Generators" option, and click "Embedded" on the right side of the page to download a file that contains information concerning your products and features called "ocelot\_feature.h".
9. Copy the files "ocelot.h" and "libocelot.ld" from the SDK library folder extracted in step 6 as well as "ocelot\_feature.h" to $(INSTALL\_ROOT)/ocelot/include/
10. Copy the lib folder to $(INSTALL\_ROOT)/ocelot/
11. Flash Ocelot DFU Bootloader
  * Erase the flash on the development kit: ```nrfjprog --eraseall```
  * Program the Ocelot DFU from the extracted Example_Product\_ocelotdfu\_X.X.X directory: ```nrfjprog --program $(OCELOT_DFU_ROOT)/bin/podboot.hex```
  * **UPDATE THIS WITH NEW TOOL USAGE WHEN IT IS AVAILABLE** Update the App ID in the DFU info record: ```nrfjprog --memwr 0x7E000 --val 0x093F736D```
  * **UPDATE THIS WITH NEW TOOL USAGE WHEN IT IS AVAILABLE** Update the CRC in the DFU info record: ```nrfjprog --memwr 0x7E00C --val 0x00000000```
12. Navigate to the Makefile of the example you wish to evaluate. For example, if you would like to evaluate the ble\_app\_blinky example, navigate to $(INSTALL\_ROOT)/obvious\_examples/ble\_peripheral/ble\_app\_blinky/pca10040/s132/armgcc
13. Set the GNU\_INSTALL\_ROOT environment variable to /usr/local/gcc-arm-none-eabi-7-2018-q2-update/bin/ and ensure that ARM GCC 7-2018-q2-update is indeed located in the aforementioned location.
14. Build the example by entering the ```make``` command.
15. Program the example onto your development kit by entering ```make flash_softdevice```, and then ```make flash```
16. **UPDATE THIS WITH NEW TOOL USAGE WHEN IT IS AVAILABLE** Back in the portal, select your product and navigate to the "Keys" page. Then, make note of your 16-byte product key. This key must be flashed onto your development board at address 0x7C000. On *nix machines, this can be accomplished by first entering the command ```echo 'PRODUCT_KEY' | xxd -r -p > product_key.bin```. Then, connect to your development kit with the JLink Commander utility and send it the command ```loadbin product_key.bin, 0x7C000```. At this point, the example can be tested with the Obvious Discover app!
17. In the Obvious Discover app, select your device from the scan menu. You may wish to filter the list by tapping the three dots on the top-right side of the screen.
18. Once your device has been selected, it will be provisioned automatically, and a feature update will occur. Notice that LED 4 on the development kit is not on. If you are evaluating the ble\_app\_uart example, notice that messages will be printed to the terminal backwards.
19. Navigate to the app's checkout tab, select your feature, and tap "Checkout". To purchase the feature, use the test Visa number 4242424242424242 with expiry 10/30 and CVV 123.
20. Once the purchase is complete, notice that LED 4 on the development board is turned on. If you are evaluating the ble\_app\_uart example, notice that messages are now printed to the terminal properly.
21. Return to the device menu and experiment with toggling the feature that was just purchased by tapping the button at the bottom of the card titled with the feature's name. In this way, the purchased feature can easily be activated and deactivated on the device!
22. Upload new firmware to your portal
  * **UPDATE THIS WITH NEW TOOL USAGE WHEN IT IS AVAILABLE** Generate a boot image from a hex file containing your built application firmware. *Internal Obvious team members can use the hex2bootimg_cli tool to produce a boot image with the following input arguments: input\_file = your\_firmware.hex, output\_file = firmware\_bootimg.hex, image\_type = 1, release = your\_release\_version, major = your\_major\_version, and minor = your\_minor\_version ```Example: hex2bootimg nrf52_xxaa.hex firmware_bootimg.hex 1 1 0 0```*
  * **UPDATE THIS WITH NEW TOOL USAGE WHEN IT IS AVAILABLE** Encrypt your boot image file using AES-128 cipher block chaining and your product key as the encryption key. *Internal Obvious team members can use the cryptaes\_cli tool to produce an encrypted boot image with the following arguments: -de = -e, -ecbcbc = -cbc, key = your\_product\_key, file\_in = firmware\_bootimg.hex, file_out = encrypted\_firmware\_bootimg.h ```Example: cryptaes -e -cbc <your\_product\_key> firmware\_bootimg.hex encrypted\_firmware\_bootimg.hex```*
  * Back in your portal, go to the "Products" tab in the top-left corner of the page and then click your product's card.
  * Click "Firmware" on the left side of the page and then select "List".
  * Click the "Add" button in the top-right corner of the page and perform the following in the dialog that pops up:
  		* Click the "Choose file" button and select your encrypted boot image.
  		* Enter Min Version 0.0.0 and Max Version 999.999.999. This defines which version of firmware can be updated to your new firmware.
  		* Enter some Release Notes, a Post Update Message, and a Comment if you wish.
  		* Click the "Create firmware" button at the bottom of the dialog.
23. Create a group for your device and add your new firmware
  * In your portal, click the "Products" tab in the top-left corner, then click "Groups" on the left side of the page.
  * Click "Add" in the top-right corner of the page and perform the following in the dialog that pops up:
  		* Name your group "Example Group".
  		* Give your example group a description if you wish.
  		* Select a priority level of 0 from the drop-down menu.
  		* Click the "Create group" button on the bottom of the dialog.
  * Click the new "Example Group" card that was just added to your groups list.
  * Click the "Add" button in the top-right corner of the page and perform the following in the dialog that pops up:
  		* Select the new firmware you added to your portal in the previous step by selecting its version from the "Select Firmware" drop-down menu.
  		* Enter 1.0.0 as your "Android Minimum Version".
  		* Enter 1.0.0 as your "iOS Minimum Version".
  		* Add a comment if you wish.
  		* Click the "Add assignment" button at the bottom of the dialog.
  * Within the "Example Group" page, select the "Devices" tab near the top of the page, NOT the "Devices" tab on the left side of the page.
  * Click the "Add" button on the right side of the page, enter your device serial number into the "Find a device to add" field of the dialog that pops up, and click the "Add device" button at the bottom of the dialog.
24. Update your device firmware OTA via the Obvious Discover app
  * In the Obvious Discover app, select your device from the scan menu. You may wish to filter the list by tapping the three dots on the top-right side of the screen.
  * Once your device has been selected, the provisioning state will be checked, and a feature update will be verified.
  * Next to "Firmware version" information there is a teal recycle button, press it and the current firmware version will be checked.
  * A prompt will appear asking if you'd like to update the firmware, select yes and your new firmware will be uploaded onto your device!

  
