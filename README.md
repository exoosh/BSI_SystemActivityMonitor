# About this project

System Activity Monitor (SAM) is a research tool that enables detailed recording of system and application behavior and resource usage. SAM uses the extremely low overhead and high speed ETW infrastructure to collect behavior and resource usage data. The decision to use ETW as a basis is mainly based on the fact, that ETW is deeply integrated into the operating system (i.e., it is an integral part of the operating system) which is equivalent to being integrated into every application that runs under Windows. SAM extends ETW and enables detailed recordings of system and application behavior and resource usage based on recording profiles, which makes it an extensive information source for research and system analysis by capturing system activity data generated during execution.

SAM recording profiles control all aspects of a recording session. A recording profile is a file in XML format that has a `.samp` extension. A recording profile contains all relevant information to enable a recording session for a specific analysis scenario. This includes configuration information about ETW sessions and providers. Each `.samp` file contains a recording profile definition, which among other things, associates a specific set of ETW providers with a recording session.

SAM by default delegates records provided by a configured ETW provider (i.e., configured in a recording profile) into Windows Event Log  system through an ETW provider with the name `SystemActivityMonitor`. The records recorded by SAM can be viewed with the Windows Event Viewer utility at the Event Viewer path `Application and Services Logs/SystemActivityMonitor/Operational`.