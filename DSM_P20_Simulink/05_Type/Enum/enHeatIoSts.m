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
            desc = '����Ӳ��״̬&#10;0���͵�ƽ&#10;1���ߵ�ƽ,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
