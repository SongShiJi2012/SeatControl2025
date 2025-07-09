%% Create enHeatIoSts enum

classdef enHeatIoSts < Simulink.IntEnumType

    enumeration
        EN_HEAT_IO_LOW(0)
        EN_HEAT_IO_HIGH(1)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enHeatIoSts.EN_HEAT_IO_LOW;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '加热硬线状态&#10;0：低电平&#10;1：高电平,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
