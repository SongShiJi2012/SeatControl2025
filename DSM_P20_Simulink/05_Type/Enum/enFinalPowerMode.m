%% Create enFinalPowerMode enum

classdef enFinalPowerMode < Simulink.IntEnumType

    enumeration
        EN_STOP_VOLT(0)
         EN_LOW_VOLT(1)
         EN_NORMAL_VOLT(2)
        EN_HIGH_VOLT(3)
        EN_OVER_VOLT(4)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enFinalPowerMode.EN_STOP_VOLT;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'µçÑ¹Ä£Ê½:&#10;0 : StopVolt&#10;1 : LowVolt&#10;2 : NormalVolt&#10;3 : HighVolt&#10;4 : OverVolt,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
