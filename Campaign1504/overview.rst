Test Campaign: April 2015
=========================

The April 2015 ground test campaign will employ fairly simple data collection
based on an Arduino Uno, which has up to 6 A/D channels.
The current plan is for only 4 channels:

  * chamber pressure
  * chamber temperature
  * propellent flow (2)

Data is collection at TBD samples/sec and written to an SD card.
The output is in the form of CSV file.

Provision is made here for both the data acquisition (DAQ) and post-processing.
The latter takes a couple of forms.

  * PostProcM - Matlab
  * PostProcP - Python

Credit to Andrew for taking the first hack. :-)
Added here (and slightly reformatted) as `DAQtest1`_.

.. _DAQtest1: DAQtest1

