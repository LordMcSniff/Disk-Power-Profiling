> [!quote] 
> In my Journey to learn PCB design I want to build my own JBOD.
> I want to power stagger and monitor the hard drives.
> Now, I *could* just rely on numbers from the Internet and LLMs, but I dont trust them.
> Scientific Method, it is! 
> > `Inspired by this TrueNAS forum thread:` https://www.truenas.com/community/threads/how-to-measure-the-drive-spin-up-peak-current.38885/

___
This repo contains the experimentation logs for all hard drive power measurements I have taken, as well as some documentation of the tools used for it.
I am primarily relying on the `INA219` & `INA226` shunt current sensors.
### TODO:
- [ ] Document stuff

- [ ] profile with base `INA219` module, low side
- [ ] profile with base `INA219` module, dual high side
- [ ] repeat profile with SATA data connected
- [ ] profile with base `INA226` module, low side
- [ ] profile with base `INA226` module, dual high side
- [ ] repeat profile with SATA data connected
- [ ] repeat profile with `R020` mod
- [ ] build PCB with `R020` `INA226` chips with differential low pass filter
- [ ] profile with `R020` `INA226` PCB, dual high side, differential low pass filter
- [ ] build PCB with `R020` `PAC1954` chip with differential low pass filter
- [ ] profile with `R020` `PAC1954` PCB
- [ ] profile with load switch
- [ ] profile different logic operations (https://gemini.google.com/app/c09b760db8b39652)
	- [ ] using the PC
	- [ ] using an ESP + USB SATA bridge
	- [ ] using a rpi z2w + USB SATA bridge
- [ ] build self contained Drive profiler
	- [ ] USB 20V PD + buck
