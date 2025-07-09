%% Create ExitGearCause enum

classdef ExitGearCause < Simulink.IntEnumType

    enumeration
        enNULL(0)
        enNotIGNOn(1)
        enRelayAdFault(2)
        enLockFault(3)
        enClearDefaultPos(4)
        enGearPrmFalse(5)
        enRunSuccess(6)
        enRunFail(7)
        enGearHallFaultFalse(8)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = ExitGearCause.enNULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '0£ºÎŞ¶¯×÷&#10;1£º&#10;2£º,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
