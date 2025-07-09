%% Create enTcmGearLvlSts enum

classdef enTcmGearLvlSts < Simulink.IntEnumType

    enumeration
        EN_TCM_INITIAL_INTERVAL(0)
        EN_TCM_PARK(1)
        EN_TCM_REVERSE(2)
        EN_TCM_NEUTRAL(3)
        EN_TCM_DRIVEE(4)
        EN_TCM_RESERVED5(5)
        EN_TCM_RESERVED6(6)
        EN_TCM_RESERVED7(7)
        EN_TCM_RESERVED8(8)
        EN_TCM_RESERVED9(9)
        EN_TCM_RESERVED10(10)
        EN_TCM_MANUAL(11)
        EN_TCM_LOW_RESERVED(12)
        EN_TCM_SPORT(13)
        EN_TCM_RESERVED14(14)
        EN_TCM_RESERVED15(15)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enTcmGearLvlSts.EN_TCM_INITIAL_INTERVAL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'TCU档位信号&#10;档位信号：&#10;0x1: P&#10;0x2: R&#10;0x3: N&#10;0x4: D&#10;0xB: M&#10;0xC: S&#10;0xF: Undefined,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
