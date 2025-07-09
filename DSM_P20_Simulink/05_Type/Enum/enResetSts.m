%% Create enResetSts enum

classdef enResetSts < Simulink.IntEnumType

    enumeration
        enInactive(0)
        enResetWaiting(1)
        enResetSuccess(2)
        enResetFail(3)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enResetSts.enInactive;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '0x0:Inactive&#10;0x1:Waiting&#10;0x2:Success&#10;0x3:Fail,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
